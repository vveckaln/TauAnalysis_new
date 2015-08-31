#include "LIP/TauAnalysis/interface/Preselector_Taus.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"
#include "LIP/TauAnalysis/interface/Register.hh"

#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "LIP/TauAnalysis/interface/Table.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/PatUtils.h"

#include "LIP/TauAnalysis/interface/Utilities.hh"
#include <math.h>
#include "TCanvas.h"
using namespace gVariables;



Preselector_Taus::Preselector_Taus(EventSink<event_type> *next_processor_stage) : EventProcessor<event_type, event_type>(next_processor_stage)
{
  selected = 0;
}

void Preselector_Taus::Run()
{
  output_event = input_event;
  print_mode = false;
  //Run 190688, lumi 99, evId 22420320
  unsigned int ntaus = PreselectTaus(); 
  if (ntaus != 1) 
    return;
  //if (processed_event -> Run == 190688 and processed_event -> Lumi == 99 and processed_event -> Event == 22420320) print_mode = true;
  //if (not print_mode) continue;
       
  if (print_mode)
    {
      printf("EVENT IDENTITY %u %u %llu\n", input_event -> Run, input_event -> Lumi, input_event -> Event);
	  
    }
  selected += input_event -> weight;    
  
  TH1D * h = utilities::GetStatisticsHistogram(number_active_sample);
  printf("Preselector_Tau %p\n", h);
  h -> Fill("1#tau", input_event -> weight);
  ProceedToNextStage();
}



unsigned int Preselector_Taus::PreselectTaus() 
{
  pat::TauCollection::iterator taus_it = input_event -> taus . begin();
  while (taus_it != input_event -> taus.end())
    {
      bool passKin(true), passId(true);
      pat::Tau * tau = &*taus_it;
      //veto nearby photon (loose electrons are many times photons...)


      //kinematics
      if(tau -> pt() < 20. || fabs(tau -> eta()) > 2.3) passKin = false;
	
	//	bool overlapWithLepton(false);
	//	for(int l1=0; l1<(int)selLeptons.size();++l1){
	//	  if(deltaR(tau, selLeptons[l1])<0.1){overlapWithLepton=true; break;}
	//	}
	//	if(overlapWithLepton) continue;
	
	//	if(!tau.isPFTau()) continue; // Only PFTaus
	//	if(tau.emFraction() >=2.) continue;
	
	if(!tau -> tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits")) passId = false;
	if(!tau -> tauID("againstMuonTight3"))                           passId = false;  
	if(!tau -> tauID("againstElectronMediumMVA5"))                   passId = false; 
	
      if(!passId || !passKin) 
	input_event -> taus.erase(taus_it);
      else
	taus_it ++;

    } 
  return input_event -> taus.size();
}

void Preselector_Taus::Report()
{
  ContinueReportToNextStage();
}

Preselector_Taus::~Preselector_Taus()
{
}
