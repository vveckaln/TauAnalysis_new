#include "LIP/TauAnalysis/interface/PileUpCorrector.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/HStructure_TFile.hh"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "LIP/TauAnalysis/interface/rootdouble.h"

#include "TROOT.h"
#include <math.h>

using namespace gVariables;
PileUpCorrector::PileUpCorrector(EventSink<DigestedEvent *> *next_processor_stage): EventProcessor<DigestedEvent*, DigestedEvent *>(next_processor_stage)
{
  topPtWeighter  = NULL;
  LumiWeights[0] = NULL;
  LumiWeights[1] = NULL;
  print_mode     = false;
  fwlite::ChainEvent & fwlite_ChainEvent = *fwlite_ChainEvent_ptr; 

  if (IsTTbarMC)
    {
      topPtWeighter = new TopPtWeighter(TString(gSystem -> BaseName(output_file_name)).ReplaceAll(".root", ""), 
					"/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/output_event_analysis",
					"/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/weights",
					fwlite_ChainEvent);
    }
  if (gIsData)
    {
      printf("isData, returning\n");
      return;
    }
  printf("continuing executing\n");
  if (gVariables::gDebug)
    XSectionWeight = gXSection/ 1100000;
  else
    {
      const double MergeableCounterValue = getMergeableCounterValue(input_file_names, "startCounter");
      XSectionWeight = gXSection/ MergeableCounterValue;
      rootdouble mcv("MergeableCounterValue", "MergeableCounterValue");
      mcv.SetInformation(MergeableCounterValue);
      for (unsigned char sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)
	{
	  ((HStructure_TFile*)active_HStructure_TFile -> GetHStructure(samples_names[sample_ind])) -> GetFile() -> cd();
	  mcv.Write();
	}
    }
  LumiWeights[0] = NULL; LumiWeights[1] = NULL;
  printf("XSectionWeiht = %f\n", XSectionWeight); 
  vector<float> MCPileUp[2]; 
  FILE *pfile[] = 
    {
      fopen("data/PileUp/dataPileupDistributionDouble.txt", "r"),
      fopen("data/PileUp/singleLepDataPileupDistributionDouble.txt", "r")
    };
  vector<float> DataPileUp[2];
  PuShifter_t PuShifters[2];

  for (unsigned char ind = /*0*/1; ind < 2; ind++)
    {
      while (not feof(pfile[ind]))
	{
	  float read_value;
	  fscanf(pfile[ind], "%e ", &read_value);
	  DataPileUp[ind].push_back(read_value);
	}
      fclose(pfile[ind]);
      getMCPileUpDistribution(fwlite_ChainEvent, DataPileUp[ind].size(), MCPileUp[ind]);
      while(MCPileUp[ind] . size() < DataPileUp[ind].size()) 
	MCPileUp[ind] . push_back(0.0);
      while(MCPileUp[ind] . size() > DataPileUp[ind].size())
	DataPileUp[ind].push_back(0.0);

      LumiWeights[ind] = new edm::LumiReWeighting(MCPileUp[ind], DataPileUp[ind]);
      PuShifters[ind] = getPUshifters(DataPileUp[ind], 0.05);
      getPileUpNormalization(MCPileUp[ind], PUNorm[ind], LumiWeights[ind], PuShifters[ind]);
     
    }
  gLumiWeights[0] = LumiWeights[0]; gLumiWeights[1] = LumiWeights[1];
}

void PileUpCorrector ::Run()
{
  output_buffer = input_buffer;
 
  for (unsigned char ind = 0; ind < input_buffer -> size(); ind ++)
    { 
    processed_event = input_buffer -> operator[](ind); 
    if (gIsData)
      {
	processed_event -> pileup_corr_weight = 1;
	continue;
      }

    double puWeight = LumiWeights[1] -> weight(processed_event -> ngenITpu) * PUNorm[1][0];
    if (print_mode)
      {
	printf("EVENT IDENTITY %u %u %u\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event);
	printf("LumiWeights = %f, PUNorm = %f, puWeight = %f\n", LumiWeights[1] -> weight(processed_event -> ngenITpu), PUNorm[1][0], puWeight);
      }
    processed_event -> pileup_corr_weight = XSectionWeight*puWeight;

    ApplyLeptonEfficiencySF();
    ApplyIntegratedLuminosity();
    ApplyTopPtWeighter();
    if (print_mode)
      {
	printf("weight = %f\n", processed_event -> pileup_corr_weight);
	printf("************** NEXT EVENT **************\n");
	getchar();
      }
    //printf("%f %f %f\n", processed_event -> pileup_corr_weight, XSectionWeight, puWeight);
    //getchar();
    //processed_event -> pileup_corr_weight = 1.0;
  }
  ProceedToNextStage();
}

void PileUpCorrector::ApplyLeptonEfficiencySF() const
{
  const Lepton * const lepton = processed_event -> GetLeadingLepton("electronmuon");
  const uint absid = lepton -> title == "electron" ? 11 : 13;
  processed_event -> pileup_corr_weight	*= 
    leptonEfficiencySF . getLeptonEfficiency(
					     lepton -> Pt(), 
					     lepton -> Eta(), 
					     absid, "tight").first;
  if (print_mode) 
    {
      printf("leptonEfficiency = %f\n",  leptonEfficiencySF . getLeptonEfficiency(
					     lepton -> Pt(), 
					     lepton -> Eta(), 
					     absid, "tight").first);
    }

}

void PileUpCorrector::ApplyIntegratedLuminosity() const
{
  const double iLumi = 19700;
  processed_event -> pileup_corr_weight *= iLumi;

}

void PileUpCorrector::ApplyTopPtWeighter() const
{
  float weightTopPt(1.0), wgtTopPtUp(1.0), wgtTopPtDown(1.0);
  if(processed_event -> tPt>0 && processed_event -> tbarPt>0 && topPtWeighter)
    {
      topPtWeighter -> computeWeight(processed_event -> tPt, processed_event -> tbarPt);
      topPtWeighter -> getEventWeight(weightTopPt, wgtTopPtUp, wgtTopPtDown);
    }
  processed_event -> pileup_corr_weight *= weightTopPt;
  if (print_mode) 
    {
      printf("weightTopPt = %f\n", weightTopPt);
    }
}

void PileUpCorrector::Report()
{
  ContinueReportToNextStage();

}

void PileUpCorrector::getMCPileUpDistribution(
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
}

unsigned long PileUpCorrector::getMergeableCounterValue(const vector<string>& urls, const string counter) const
{
  unsigned long Total = 0;
  for(unsigned int f_ind = 0; f_ind < urls.size(); f_ind++)
    {
      TFile *file = TFile::Open(urls[f_ind].c_str());      
      fwlite::LuminosityBlock ls(file);
      for(ls.toBegin(); !ls.atEnd(); ++ls)
	{
	  fwlite::Handle<edm::MergeableCounter> nEventsTotalCounter;
	  nEventsTotalCounter.getByLabel(ls,counter.c_str());
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
}


PileUpCorrector::~PileUpCorrector()
{
  if (topPtWeighter)
    {
      delete topPtWeighter;
      topPtWeighter = NULL;
    }
  for (short ind = 0; ind < 2; ind ++)
    {
      if (LumiWeights[ind])
	{
	  delete LumiWeights[ind];
	  LumiWeights[ind] = NULL;
	}
    }
}
