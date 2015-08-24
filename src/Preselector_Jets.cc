#include "LIP/TauAnalysis/interface/Preselector_Jets.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"
#include "LIP/TauAnalysis/interface/Register.hh"

#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "LIP/TauAnalysis/interface/Table.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/PatUtils.h"

#include <math.h>
#include "TCanvas.h"
using namespace gVariables;

Preselector_Jets::Preselector_Jets(EventSink<event_type> *next_processor_stage):EventProcessor<event_type, event_type>(next_processor_stage)
{
  
}

void Preselector_Jets::Run()
{
  output_buffer = input_buffer;
  for (it = input_buffer -> begin(); it != input_buffer -> end(); it ++)
    { 
      unsigned int njets = PreselectJets();
      unsigned int njets_tau(0);
      for (unsigned int ind = 0; ind < it -> jets.size(); ind ++)
	{
	  if (it -> jets[ind].pt() > 30) njets_tau ++;

	}
      if (not (njets > 2 and  njets_tau > 1)) 
	input_buffer -> erase(it);
      print_mode = false;
      //Run 190688, lumi 99, evId 22420320



      //if (processed_event -> Run == 190688 and processed_event -> Lumi == 99 and processed_event -> Event == 22420320) print_mode = true;
      //if (not print_mode) continue;
       
      if (print_mode)
	{
	  printf("EVENT IDENTITY %u %u %u\n", it -> Run, it -> Lumi, it -> Event);
	  
	}
      
      if (output_buffer -> IsFull())
	{
	  ProceedToNextStage();
	  
	}
    }
  if (!output_buffer -> IsEmpty())
    {
      ProceedToNextStage();
     }
}

unsigned int Preselector_Jets::PreselectJets()
{
  const GeV JET_PT_MIN            = 20;
  const double JET_ETA_MAX        = 2.4;
  const double JET_LEPTON_DR_MIN  = 0.3;//0.4;
    
  pat::JetCollection::iterator jets_it = it -> jets.begin();
  do
    {
      pat::Jet * jet = &*jets_it;
      bool passKin(true);
  
      if(jet -> pt() < JET_PT_MIN/*15*/ || fabs(jet -> eta()) > JET_ETA_MAX/*4.7*/) passKin = false;
      if (passKin)
	{
	  //mc truth for this jet
	  const reco::GenJet* genJet = jet -> genJet();
	  TString jetType( genJet && genJet -> pt() > 0 ? "truejetsid" : "pujetsid" );

	  //cross-clean with selected leptons and photons
	  double minDRlj(9999.);
	  const size_t lepton_size[2] = {it -> electrons.size(), it -> muons.size()};
	  for (unsigned char type = 0; type < 2; type ++)
	    {
	      for(size_t ilep = 0; ilep < lepton_size[type]; ilep ++)
		{
		  minDRlj = TMath::Min(minDRlj, type == 0 ? deltaR(*jet, it -> electrons[ilep]) : deltaR(*jet, it -> muons[ilep]));
	  
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
      
      if(!passKin || !passPFloose || !passLooseSimplePuId) it -> jets.erase(jets_it);
      if (jets_it != it -> jets.end()) jets_it ++;
    }while (jets_it != it -> jets.end());
  return it -> jets.size();
      
}

void Preselector_Jets::Report()
{
}

Preselector_Jets::~Preselector_Jets()
{
}
