#include "LIP/TauAnalysis/interface/Preselector_Taus.hh"
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



Preselector_Taus::Preselector_Taus(EventSink<event_type> *next_processor_stage) : EventProcessor<event_type, event_type>(next_processor_stage)
{
  
}

void Preselector_Taus::Run()
{
  output_buffer = input_buffer;
  for (it = input_buffer -> begin(); it != input_buffer -> end(); it ++)
    { 
     
      print_mode = false;
      //Run 190688, lumi 99, evId 22420320
      unsigned int ntaus = PreselectTaus(); 
      if (ntaus != 1) 
	input_buffer -> erase(it);

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



unsigned int Preselector_Taus::PreselectTaus() 
{
  pat::TauCollection::iterator taus_it = it -> taus . begin();
  do
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
	
      if(!passId || !passKin)          it -> taus.erase(taus_it);
      if (taus_it != it -> taus . end()) taus_it ++;

    } while(taus_it != it -> taus . end());
  return it -> taus.size();
}

void Preselector_Taus::Report()
{
}

Preselector_Taus::~Preselector_Taus()
{
}
