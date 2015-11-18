#include "LIP/TauAnalysis/interface/PileUpCorrector.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/HStructure_TFile.hh"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "LIP/TauAnalysis/interface/rootdouble.h"
#include "LIP/TauAnalysis/interface/MacroUtils.h"
#include "LIP/TauAnalysis/interface/Utilities.hh"

#include "TROOT.h"
#include <math.h>

using namespace gVariables;
PileUpCorrector::PileUpCorrector(EventSink<event_type> *next_processor_stage): EventProcessor<event_type, event_type>(next_processor_stage)
{
  LumiWeights = NULL;
  
  print_mode     = false;
  fwlite::ChainEvent & fwlite_ChainEvent = *fwlite_ChainEvent_ptr;
 
  if (gIsData)
    {
      return;
    }
  const double MergeableCounterValue = /*gVariables::gDebug ? 45000 :  */utils::getTotalNumberOfEvents(input_file_names, true); //getMergeableCounterValue(input_file_names, "startCounter");
  XSectionWeight = gXSection/ MergeableCounterValue;
  rootdouble mcv("MergeableCounterValue", "MergeableCounterValue");
  mcv.SetInformation(MergeableCounterValue);
  for (unsigned char sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)
    {
      ((HStructure_TFile*)active_HStructure_TFile -> GetHStructure(samples_names[sample_ind])) -> GetFile() -> cd();
      mcv.Write();
    }

  vector<float> MCPileUp; 
  FILE * pfile = fopen("data/PileUp/datapileup_200pb_2015bcd_ll_Preliminary.txt", "r");
  vector<float> DataPileUp;
  PuShifter_t PuShifters;

  while (not feof(pfile))
    {
      float read_value;
      fscanf(pfile, "%e ", &read_value);
      DataPileUp.push_back(read_value);
    }
  fclose(pfile);
  utils::getMCPileupDistributionFromMiniAOD(input_file_names, DataPileUp.size(), MCPileUp);
  while(MCPileUp . size() < DataPileUp.size()) 
    MCPileUp . push_back(0.0);
  while(MCPileUp . size() > DataPileUp.size())
    DataPileUp.push_back(0.0);

  LumiWeights = new edm::LumiReWeighting(MCPileUp, DataPileUp);
  PuShifters = utils::cmssw::getPUshifters(DataPileUp, 0.05);
  utils::getPileupNormalization(MCPileUp, PUNorm, LumiWeights, PuShifters);
  gLumiWeights[0] = LumiWeights; 
}

void PileUpCorrector ::Run()
{
  
  output_event = input_event;
  if (gIsData)
    {
      input_event -> weight = 1;
      ProceedToNextStage();
      TH1D *h = utilities::GetSelectorHistogram();
      h -> Fill("read", input_event -> weight);
      return;
    }
  int ngenITpu = 0;
  for(vector<PileupSummaryInfo>::const_iterator it = input_event -> PU.begin(); it != input_event -> PU.end(); it++)
    {
      if(it -> getBunchCrossing() == 0) 
	{ 
	  ngenITpu += it -> getPU_NumInteractions(); 
	}
    }
  const double puWeight = LumiWeights -> weight(ngenITpu) * PUNorm[0];
  if (print_mode)
    {
      printf("EVENT IDENTITY %u %u %llu\n", input_event -> Run, input_event -> Lumi, input_event -> Event);
      printf("LumiWeights = %f, PUNorm = %f, puWeight = %f\n", LumiWeights -> weight(ngenITpu), PUNorm[0], puWeight);
    }
  float shapeWeight = 1.0;
  if(input_event -> genEventInfo.weight() < 0)
    {
      shapeWeight *= -1;
    }
  input_event -> weight = XSectionWeight*puWeight*shapeWeight;
    
  //ApplyLeptonEfficiencySF();
  ApplyIntegratedLuminosity();
  ApplyTopPtWeighter();
  if (print_mode)
    {
      printf("weight = %f\n", input_event -> weight);
      printf("************** NEXT EVENT **************\n");
      getchar();
    }
  //getchar();
  //processed_event -> pileup_corr_weight = 1.0;
  TH1D *h = utilities::GetSelectorHistogram();
  h -> Fill("read", input_event -> weight);
  
  ProceedToNextStage();
}

void PileUpCorrector::ApplyLeptonEfficiencySF() const
{
  
  const reco::LeafCandidate * const lepton = input_event -> electrons.size() == 1 ?( reco::LeafCandidate*)&input_event -> electrons[0] : 
    (reco::LeafCandidate*)&input_event -> muons[0];
  const uint absid = fabs(lepton -> pdgId());
  input_event -> weight	*= 
    leptonEfficiencySF . getLeptonEfficiency(
					     lepton -> pt(), 
					     lepton -> eta(), 
					     absid, "tight").first;
  if (print_mode) 
    {
      printf("leptonEfficiency = %f\n",  leptonEfficiencySF . getLeptonEfficiency(
					     lepton -> pt(), 
					     lepton -> eta(), 
					     absid, "tight").first);
    }

}

void PileUpCorrector::ApplyIntegratedLuminosity() const
{
  const double iLumi = 14.6/*19700*/;
  input_event -> weight *= iLumi;

}

void PileUpCorrector::ApplyTopPtWeighter() const
{
  /*float weightTopPt(1.0), wgtTopPtUp(1.0), wgtTopPtDown(1.0);
  if(processed_event -> tPt>0 && processed_event -> tbarPt>0 && topPtWeighter)
    {
      topPtWeighter -> computeWeight(processed_event -> tPt, processed_event -> tbarPt);
      topPtWeighter -> getEventWeight(weightTopPt, wgtTopPtUp, wgtTopPtDown);
    }
  processed_event -> pileup_corr_weight *= weightTopPt;
  if (print_mode) 
    {
      printf("weightTopPt = %f\n", weightTopPt);
      }*/
}

void PileUpCorrector::Report()
{
  ContinueReportToNextStage();

}

/*void PileUpCorrector::getMCPileUpDistribution(
				    fwlite::ChainEvent& fwlite_ChainEvent, 
				    const unsigned int Npu, 
				    vector<float> & MCPileUp)
{
  MCPileUp.clear();
    MCPileUp.resize(Npu);
    for(Long64_t ientry = 0; ientry < fwlite_ChainEvent.size(); ientry++)
      {
	fwlite_ChainEvent.to(ientry);
	fwlite::Handle< llvvGenEvent > genEventHandle;
	genEventHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed");
	if(!genEventHandle.isValid())
	  {
	    continue;
	  } 
	unsigned int ngenITpu = (int)genEventHandle -> ngenITpu;
	if(ngenITpu >= Npu)
	  {
	    printf("ngenITpu is larger than vector size... vector is being resized, but you should check that all is ok!"); 
	    MCPileUp.resize(ngenITpu+1);
	  }
	MCPileUp[ngenITpu]++;
	}
}

PuShifter_t PileUpCorrector::getPUshifters(vector<float> &Lumi_distr, const float puUnc) const
{
  const uint NBins = Lumi_distr.size();
  TH1F * const pu     = new TH1F("putmp", "", NBins, -0.5, float(NBins)-0.5);
  TH1F * const puup   = (TH1F *)pu -> Clone("puuptmp");
  TH1F * const pudown = (TH1F *)pu -> Clone("pudowntmp");
  for(size_t i = 0; i < Lumi_distr.size(); i++)
    pu -> SetBinContent(i+1, Lumi_distr[i]);
  for(int ibin = 1; ibin <= pu -> GetXaxis() -> GetNbins(); ibin++)
    {
      const Double_t xval = pu -> GetBinCenter(ibin);
      TGraph * const gr = new TGraph;
      for(int ishift = -3; ishift < 3; ishift++)
	{
	  if(ibin + ishift < 0) continue;
	  if(ibin + ishift > pu -> GetXaxis() -> GetNbins()) continue;
	  gr -> SetPoint(gr -> GetN(), 
			 xval + ishift, 
			 pu -> GetBinContent(ibin + ishift));
	}
      if(gr -> GetN() > 1)
	{
	  const double newval_down(gr -> Eval(xval*(1 + puUnc)));
	  pudown -> SetBinContent(ibin, newval_down > 0 ? newval_down : 0.0);
	  const double newval_up = gr -> Eval(xval*(1 - puUnc));
	  puup -> SetBinContent(ibin, newval_up > 0 ? newval_up : 0.0);
	}
      delete gr;
    }
  puup   -> Scale(pu -> Integral()/puup   -> Integral());
  pudown -> Scale(pu -> Integral()/pudown -> Integral());
  cout << "getPUshifts will shift average PU by " << 
    puup   -> GetMean() - pu -> GetMean() << " / " << 
    pudown -> GetMean() - pu -> GetMean() <<endl; 
  PuShifter_t res(2);
  puup   -> Divide(pu); res[PUUP]   = new TGraph(puup);
  pudown -> Divide(pu); res[PUDOWN] = new TGraph(pudown);
  delete puup;
  delete pudown;  
  delete pu;
  return res;
}
  
void PileUpCorrector::getPileUpNormalization(
					   vector<float>& mcpileup, 
					   double* PUNorm, 
					   edm::LumiReWeighting* LumiWeights,                                                                              PuShifter_t PuShifters) const
{
  PUNorm[0] = 0; PUNorm[1] = 0; PUNorm[2] = 0;
  double NEvents = 0;
  for(unsigned int ind = 0; ind < mcpileup.size(); ind ++)
    {
      NEvents += mcpileup[ind];
      const double puWeight = LumiWeights -> weight((int)ind);
      PUNorm[0] += mcpileup[ind]*puWeight;
      PUNorm[1] += mcpileup[ind]*puWeight*PuShifters[PUDOWN] -> Eval(ind);
      PUNorm[2] += mcpileup[ind]*puWeight*PuShifters[PUUP]   -> Eval(ind);
    }
  PUNorm[0]/=NEvents;
  PUNorm[1]/=NEvents;
  PUNorm[2]/=NEvents;
  }*/

/*unsigned long PileUpCorrector::getMergeableCounterValue(const vector<string>& urls, const string counter) const
{
  unsigned long Total = 0;
  for(unsigned int f_ind = 0; f_ind < urls.size(); f_ind++)
    {
      TFile *file = TFile::Open(urls[f_ind].c_str());      
      fwlite::LuminosityBlock ls(file);
      for(ls.toBegin(); !ls.atEnd(); ++ls)
	{
	  fwlite::Handle<edm::MergeableCounter> nEventsTotalCounter;
	  nEventsTotalCounter.getByLabel(ls, counter.c_str());
	  if(!nEventsTotalCounter.isValid())
	    {
	      printf("Invalid nEventsTotalCounterH\n");
	      continue;
	    }
	  Total += nEventsTotalCounter -> value;
	}
      file -> Close();
   }
 return Total;
}*/


PileUpCorrector::~PileUpCorrector()
{
  
  if (LumiWeights)
    {
      delete LumiWeights;
      LumiWeights = NULL;
    }
  
}
