#include "TauAnalysis/interface/Preselector_Leptons.hh"
#include "TauAnalysis/interface/GlobalVariables.hh"
#include "TauAnalysis/interface/HStructure_worker.hh"
#include "TauAnalysis/interface/Register.hh"
#include "TauAnalysis/interface/Utilities.hh"

#include "TauAnalysis/interface/Table.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "TauAnalysis/interface/GlobalVariables.hh"
#include "TauAnalysis/interface/PatUtils.h"
#include "TauAnalysis/interface/LeptonSelectionDefinitions.hh"

#include <math.h>
#include "TCanvas.h"
using namespace gVariables;



Preselector_Leptons::Preselector_Leptons(EventSink<event_type> *next_processor_stage):EventProcessor<event_type, event_type>(next_processor_stage)
{
  selected = 0;
 }

void Preselector_Leptons::Run()
{
  output_event = input_event;
  vtx = &input_event -> vertices[0];   
  muons_ptr.clear();
  electrons_ptr.clear();
  for (size_t ind = 0; ind < input_event -> electrons.size(); ind ++) 
    {
      electrons_ptr.push_back(&input_event -> electrons[ind]);
    }
  for (size_t ind = 0; ind < input_event -> muons.size(); ind ++) 
    muons_ptr.push_back(&input_event -> muons[ind]);
  unsigned int nselected_electrons;
  nselected_electrons = PreselectElectrons();
  unsigned int nselected_muons     = PreselectMuons();
  if (nselected_electrons + nselected_muons != 1) 
    {
      return;
    }
  TH1D *h = utilities::GetSelectorHistogram();
  
  h -> Fill("1 lepton", input_event -> weight);
  unsigned int nVeto_electrons = VetoLooseElectrons();
  unsigned int nVeto_muons     = VetoLooseMuons();
  if (nVeto_electrons + nVeto_muons > 0) 
    {
      return;
    }
  h -> Fill("no loose leptons", input_event -> weight);
  if (nselected_electrons == 1)
    {
      vector<pat::Electron> vect;
      vect.push_back(*electrons_ptr.at(0));
      input_event -> electrons = vect;
      input_event -> muons.clear();
    }

  if (nselected_muons == 1)
    {
      vector<pat::Muon> vect;
      vect.push_back(*muons_ptr.at(0));
      input_event -> muons = vect;
      input_event -> electrons.clear();
    }
  print_mode = false;
       
  if (print_mode)
    {
      printf("EVENT IDENTITY %u %u %llu\n", input_event -> Run, input_event -> Lumi, input_event -> Event);
	  
    }
      
  ProceedToNextStage();
     
}



unsigned int Preselector_Leptons::PreselectElectrons() 
{
  
  vector<pat::Electron*>::iterator el_it = electrons_ptr.begin();
  while (el_it != electrons_ptr.end())
    {
      bool passKin(true), passId(true), passIso(true);
      electron = *el_it;
      const float leta = fabs(electron -> superCluster() -> eta());
      if(leta > 2.5)                     
	passKin = false;
      if(leta > 1.4442 && leta < 1.5660) 
	passKin = false;

      if(electron -> pt() < 35)  
	passKin = false;

      //Cut based identification
      passId = passIdElectron(ElecId::Tight);

      //isolation
      passIso = patUtils::passIso(*electron,  patUtils::llvvElecIso::Tight);

      if(not (passId && passIso && passKin))    
	electrons_ptr.erase(el_it);
      else
	el_it ++;

    } ;
  return electrons_ptr.size();
  
}
 
unsigned int Preselector_Leptons::PreselectMuons()  
{
  vector<pat::Muon*>::iterator muon_it = muons_ptr.begin();
  while (muon_it != muons_ptr.end())
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
	muons_ptr.erase(muon_it);
      else
	muon_it ++;

    };
  return muons_ptr.size();
 
}

unsigned int Preselector_Leptons::VetoLooseElectrons()  
{
  //double const ref_rel_isolation        = 0.2;
  GeV const    ref_Pt                   = 15;
  double const ref_eta               = 2.5;
  const double ETA_EXCLUSION_REGION_MIN = 1.4442;
  const double ETA_EXCLUSION_REGION_MAX = 1.5660;
  unsigned char nVeto_electrons(0);
  void * lepton = muons_ptr.size() == 1 ? (void*)muons_ptr.at(0) : (void*)electrons_ptr.at(0);

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
      passId = passIdElectron(ElecId::Loose);
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
  void * lepton = muons_ptr.size() == 1 ? (void*)muons_ptr.at(0) : (void*)electrons_ptr.at(0);

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

bool Preselector_Leptons::passIdElectron(const unsigned char IdLevel) const
{
    
  //for electron Id look here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2
  //for the meaning of the different cuts here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaCutBasedIdentification
  const float sigmaletaleta  = electron -> full5x5_sigmaIetaIphi();
  const float dEtaln         = fabs(electron -> deltaEtaSuperClusterTrackAtVtx());
  const float dPhiln         = fabs(electron -> deltaPhiSuperClusterTrackAtVtx());
  const float hem            = electron -> hadronicOverEm();
  float ooEmooP = 0;
  if( electron -> ecalEnergy() == 0 ){
     ooEmooP = 1e30;
  }else if( !std::isfinite(electron -> ecalEnergy())){
    printf("Electron energy is not finite!\n");
    ooEmooP = 1e30 ;
  }else{
    ooEmooP = fabs(1.0/electron->ecalEnergy() - electron->eSuperClusterOverP()/electron->ecalEnergy() ) ;
  }
  const double resol         = fabs(1/electron -> ecalEnergy() - 1/electron -> trackMomentumAtVtx().pt());
  const double dxy           = fabs(electron -> gsfTrack() -> dxy(vtx -> position()));
  const double dz            = fabs(electron -> gsfTrack() -> dz(vtx -> position())); 
  const double mHits         = electron -> gsfTrack() -> trackerExpectedHitsInner().numberOfHits();//hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
    
  const bool barrel = (fabs(electron -> superCluster() -> eta()) <= 1.479);
  const bool endcap = (!barrel && fabs(electron -> superCluster() -> eta()) < 2.5);
  unsigned char region = 0;
  if (endcap) 
    region = 1;
  //Veto Loose Medium Tight
  

  if (
      sigmaletaleta < full5x5_sigmaIetaIeta_ref[grun][region][IdLevel] and
      dEtaln < abs_dEtaIn_ref[grun][region][IdLevel] and
      dPhiln < abs_dPhiIn_ref[grun][region][IdLevel] and
      hem < hOverE_ref[grun][region][IdLevel] and 
      resol < relIsoWithEA_ref[grun][region][IdLevel] and
      dxy < abs_d0_ref[grun][region][IdLevel] and
      dz < abs_dz_ref[grun][region][IdLevel] and
      mHits < expectedMissingInngerHits[grun][region][IdLevel])
    return true;
  return false;
}

void Preselector_Leptons::Report()
{
  printf("Selected leptons %f\n", selected);
  ContinueReportToNextStage();
}

Preselector_Leptons::~Preselector_Leptons()
{
}
