#include "LIP/TauAnalysis/interface/Preselector_Leptons.hh"
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



Preselector_Leptons::Preselector_Leptons(EventSink<event_type> *next_processor_stage):EventProcessor<event_type, event_type>(next_processor_stage)
{
  selected = 0;
  electrons_ptr = new vector<pat::Electron*>;
  muons_ptr = new vector<pat::Muon*>;
}

void Preselector_Leptons::Run()
{
  output_event = input_event;
     
  muons_ptr -> clear();
  electrons_ptr -> clear();


  //printf("size %lu \n", electrons_ptr -> size());
      //  electrons_ptr -> clear();
  for (size_t ind = 0; ind < input_event -> electrons.size(); ind ++) 
    {
      electrons_ptr -> push_back(&input_event -> electrons[ind]);
    }
  for (size_t ind = 0; ind < input_event -> muons.size(); ind ++) 
    muons_ptr -> push_back(&input_event -> muons[ind]);
  unsigned int nselected_electrons;
  try
    {
      nselected_electrons = PreselectElectrons();
    } catch (const char* e)
    {
      printf("caught %s\n", e);
      return;
    }
  unsigned int nselected_muons     = PreselectMuons();
  if (nselected_electrons + nselected_muons > 1 or nselected_electrons + nselected_muons == 0) 
    {
      //input_buffer -> erase(it);
      return;
    }
  unsigned int nVeto_electrons;
  try
    {
      nVeto_electrons = VetoLooseElectrons();
    } catch (const char* e)
    {
      printf("caught %s\n", e);
      return;
    }
  unsigned int nVeto_muons     = VetoLooseMuons();
  if (nVeto_electrons + nVeto_muons > 0) 
    {
      //input_buffer -> erase(it);
      return;
    }
  if (nselected_electrons == 1)
    {
      vector<pat::Electron> vect;
      vect.push_back(*electrons_ptr -> at(0));
      input_event -> electrons = vect;
    }

  if (nselected_muons == 1)
    {
      vector<pat::Muon> vect;
      vect.push_back(*muons_ptr -> at(0));
      input_event -> muons = vect;
    }
  print_mode = false;
  //Run 190688, lumi 99, evId 22420320



  //if (processed_event -> Run == 190688 and processed_event -> Lumi == 99 and processed_event -> Event == 22420320) print_mode = true;
  //if (not print_mode) continue;
       
  if (print_mode)
    {
      printf("EVENT IDENTITY %u %u %llu\n", input_event -> Run, input_event -> Lumi, input_event -> Event);
	  
    }
      
  // if (output_buffer -> IsFull())
  selected ++;
  ProceedToNextStage();
	  
	  //  }
  //if (!output_buffer -> IsEmpty())
    
  //ProceedToNextStage();*/
     
}



unsigned int Preselector_Leptons::PreselectElectrons() 
{
  
  vector<pat::Electron*>::iterator el_it = electrons_ptr -> begin();
  while (el_it != electrons_ptr -> end())
    {
      bool passKin(true), passId(true), passIso(true);
      pat::Electron * electron = *el_it;
      //veto nearby photon (loose electrons are many times photons...)
      //kinematics
      if (not electron -> superCluster())
	throw "no superCluster";
      const float leta = fabs(electron -> superCluster() -> eta());
      if(leta > 2.5)                     
	passKin = false;
      if(leta > 1.4442 && leta < 1.5660) 
	passKin = false;

      if(electron -> pt() < 35)  
	passKin = false;

      //Cut based identification
      passId = patUtils::passId(*electron, input_event -> vertices[0], patUtils::llvvElecId::Tight);

      //isolation
      passIso = patUtils::passIso(*electron,  patUtils::llvvElecIso::Tight);

      if(not (passId && passIso && passKin))    
	electrons_ptr -> erase(el_it);
      else
	el_it ++;

    } ;
  return electrons_ptr -> size();
  
}
 
unsigned int Preselector_Leptons::PreselectMuons()  
{
  vector<pat::Muon*>::iterator muon_it = muons_ptr -> begin();
  while (muon_it != muons_ptr -> end())
    {
      bool passKin(true), passId(true), passIso(true);
      pat::Muon * muon = *muon_it;
      //veto nearby photon (loose electrons are many times photons...)


      //kinematics
      const float leta = fabs(muon -> eta());
      if(leta > 2.1)            passKin = false;
      if(muon -> pt() < 30)     passKin = false;

	  //Cut based identification
      passId = patUtils::passId(*muon, input_event -> vertices[0], patUtils::llvvMuonId::Tight);

	  //isolation
      passIso = patUtils::passIso(*muon,  patUtils::llvvMuonIso::Tight);
     
      if(not (passId && passIso && passKin)) 
	muons_ptr-> erase(muon_it);
      else
	muon_it ++;

    };
  return muons_ptr-> size();
 
}

unsigned int Preselector_Leptons::VetoLooseElectrons()  
{
  //double const ref_rel_isolation        = 0.2;
  GeV const    ref_Pt                   = 15;
  double const ref_eta               = 2.5;
  const double ETA_EXCLUSION_REGION_MIN = 1.4442;
  const double ETA_EXCLUSION_REGION_MAX = 1.5660;
  unsigned char nVeto_electrons(0);
  void * lepton = muons_ptr -> size() == 1 ? (void*)muons_ptr -> at(0) : (void*)electrons_ptr -> at(0);

  for (ushort ind = 0; ind < input_event -> electrons.size(); ind ++)
    {
      bool passKin(true), passId(true), passIso(true);
      pat::Electron * const electron = &input_event -> electrons[ind]; 
      if (lepton == electron) continue;

      //if (IsSingleMuPD and lepton -> title == "electron") return false;
      const GeV    Pt                       = electron -> pt();
      if (not electron -> superCluster())
	throw "no superCluster";
      const float AbsEta = fabs(electron -> superCluster() -> eta());

      if(Pt < ref_Pt) 
	passKin = false;
      if(AbsEta < ref_eta)
	passKin = false;
      if (AbsEta > ETA_EXCLUSION_REGION_MIN and AbsEta < ETA_EXCLUSION_REGION_MAX) 
	passKin = false;
      passId = patUtils::passId(*electron, input_event -> vertices[0], patUtils::llvvElecId::Loose);
      passIso = patUtils::passIso(*electron, patUtils::llvvElecIso::Loose);
      
      if (passId and passIso and passKin)
	{
	  nVeto_electrons ++;
	}
    }
  return nVeto_electrons;
}

unsigned int Preselector_Leptons::VetoLooseMuons()  
{
  GeV const    ref_Pt                   = 10;
  double const ref_eta               = 2.5;
  
  unsigned char nVeto_muons(0);
  void * lepton = muons_ptr -> size() == 1 ? (void*)muons_ptr -> at(0) : (void*)electrons_ptr -> at(0);

  for (ushort ind = 0; ind < input_event -> muons.size(); ind ++)
    {
      bool passKin(true), passId(true), passIso(true);
      pat::Muon * const muon = &input_event -> muons[ind]; 
      if (lepton == muon) continue;

      //if (IsSingleMuPD and lepton -> title == "electron") return false;
      const GeV    Pt    = muon -> pt();
      const float AbsEta = fabs(muon -> eta());

      if(Pt < ref_Pt) 
	passKin = false;
      if(AbsEta < ref_eta)
	passKin = false;
      

      passId = patUtils::passId(*muon, input_event -> vertices[0], patUtils::llvvMuonId::Loose);
      passIso = patUtils::passIso(*muon, patUtils::llvvMuonIso::Loose);
      
      if (passId and passIso and passKin)
	{
	  nVeto_muons ++;
	}
    }
  return nVeto_muons;
}

void Preselector_Leptons::Report()
{
  printf("Selected leptons %f\n", selected);
  ContinueReportToNextStage();
}

Preselector_Leptons::~Preselector_Leptons()
{
}
