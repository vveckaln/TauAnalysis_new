#include "CERN_RTU/TauAnalysis/interface/Preselector_Jets.hh"
#include "CERN_RTU/TauAnalysis/interface/GlobalVariables.hh"
#include "CERN_RTU/TauAnalysis/interface/HStructure_worker.hh"
#include "CERN_RTU/TauAnalysis/interface/Register.hh"
#include "CERN_RTU/TauAnalysis/interface/Utilities.hh"

#include "CERN_RTU/TauAnalysis/interface/llvvObjects.h"
#include "CERN_RTU/TauAnalysis/interface/Table.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "CERN_RTU/TauAnalysis/interface/GlobalVariables.hh"
#include "CERN_RTU/TauAnalysis/interface/PatUtils.h"

#include <math.h>
#include "TCanvas.h"
using namespace gVariables;

Preselector_Jets::Preselector_Jets(EventSink<event_type> *next_processor_stage):EventProcessor<event_type, event_type>(next_processor_stage)
{
  selected = 0;
}

void Preselector_Jets::Run()
{
  output_event = input_event;
  unsigned int njets = PreselectJets();
  if (njets < 2)
    return;
  TH1D *h = utilities::GetSelectorHistogram();
  h -> Fill("2 jets", input_event -> weight);
  print_mode = false;
       
  if (print_mode)
    {
      printf("EVENT IDENTITY %u %u %llu\n", input_event -> Run, input_event -> Lumi, input_event -> Event);
	  
    }
      
  selected ++;
  ProceedToNextStage();
}

unsigned int Preselector_Jets::PreselectJets()
{
  const GeV JET_PT_MIN            = 20;
  const double JET_ETA_MAX        = 2.4;
  const double JET_LEPTON_DR_MIN  = 0.3;//0.4;
    
  pat::JetCollection::iterator jets_it = input_event -> jets.begin();
  while(jets_it != input_event -> jets.end())
    {
      pat::Jet * jet = &*jets_it;
      bool isTauJet(false);
      if (deltaR(*jet, input_event -> taus[0]) < 0.2 ) 
	isTauJet = true;
      bool passKin(true);
  
      if(jet -> pt() < JET_PT_MIN/*15*/ || fabs(jet -> eta()) > JET_ETA_MAX/*4.7*/) passKin = false;
      if (passKin)
	{
	  //mc truth for this jet
	  /*const reco::GenJet* genJet = jet -> genJet();
	    TString jetType( genJet && genJet -> pt() > 0 ? "truejetsid" : "pujetsid" );*/

	  //cross-clean with selected leptons and photons
	  double minDRlj(9999.);
	  const size_t lepton_size[2] = {input_event -> electrons.size(), input_event -> muons.size()};
	  for (unsigned char type = 0; type < 2; type ++)
	    {
	      for(size_t ilep = 0; ilep < lepton_size[type]; ilep ++)
		{
		  minDRlj = TMath::Min(minDRlj, type == 0 ? deltaR(*jet, input_event -> electrons[ilep]) : deltaR(*jet, input_event -> muons[ilep]));
	  
		  if(minDRlj < JET_LEPTON_DR_MIN/*0.4*/) 
		    {
		      passKin = false;
		      continue;
		    }
		}
	    }
	}
      //jet id
      bool passPFloose = patUtils::passPFJetID("Loose", *jet);
      //float PUDiscriminant = jet -> userFloat("pileupJetId:fullDiscriminant");
      bool passLooseSimplePuId = patUtils::passPUJetID(*jet); //Uses recommended value of HZZ, will update this as soon my analysis is done. (Hugo)
      
      if(isTauJet || !passKin || !passPFloose || !passLooseSimplePuId) 
	input_event -> jets.erase(jets_it);
      else
	jets_it ++;
    };
  return input_event -> jets.size();
      
}

void Preselector_Jets::Report()
{
  printf("Selected jets %f\n", selected);
  ContinueReportToNextStage();
}

Preselector_Jets::~Preselector_Jets()
{
}
