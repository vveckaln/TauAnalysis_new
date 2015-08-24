#include "LIP/TauAnalysis/interface/Preselector.hh"
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



Preselector::Preselector(EventSink<event_type> *next_processor_stage):EventProcessor<event_type, event_type>(next_processor_stage)
{
  
}

void Preselector::Run()
{
  output_buffer = input_buffer;
  for (unsigned char ind = 0; ind < input_buffer -> size(); ind ++)
    { 
      processed_event = &(*input_buffer)[ind];
      
      print_mode = false;
      //Run 190688, lumi 99, evId 22420320



      //if (processed_event -> Run == 190688 and processed_event -> Lumi == 99 and processed_event -> Event == 22420320) print_mode = true;
      //if (not print_mode) continue;
       
      if (print_mode)
	{
	  printf("EVENT IDENTITY %u %u %u\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event);
	  
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



void Preselector::PreselectElectrons() const
{
  pat::ElectronCollection::iterator it = processed_event -> electrons . begin();
  do
    {
      bool passKin(true), passId(true), passIso(true);
      pat::Electron * electron = &*it;
      //veto nearby photon (loose electrons are many times photons...)


      //kinematics
      const float leta = electron -> superCluster() -> eta();
      if(leta > 2.5)                      passKin = false;
      if(leta > 1.4442 && leta < 1.5660) passKin = false;

      if(electron -> pt() < 20)  passKin=false;

      //Cut based identification
      passId = patUtils::passId(*electron, processed_event -> vertices[0], patUtils::llvvElecId::Tight);

      //isolation
      passIso = patUtils::passIso(*electron,  patUtils::llvvElecIso::Tight);

      if(not (passId && passIso && passKin))          processed_event -> electrons.erase(it);
      if (it != processed_event -> electrons . end()) it ++;

    } while(it != processed_event -> electrons . end());
  
}
 
void Preselector::PreselectMuons() const
{
  pat::MuonCollection::iterator it = processed_event -> muons . begin();
  do
    {
      bool passKin(true), passId(true), passIso(true);
      pat::Muon * muon = &*it;
      //veto nearby photon (loose electrons are many times photons...)


      //kinematics
      const float leta = muon -> eta();
      if(leta > 2.4)            passKin = false;
      if(muon -> pt() < 20)     passKin=false;

	  //Cut based identification
      passId = patUtils::passId(*muon, processed_event -> vertices[0], patUtils::llvvMuonId::Tight);

	  //isolation
      passIso = patUtils::passIso(*muon,  patUtils::llvvMuonIso::Tight);
     
      if(not (passId && passIso && passKin))          processed_event -> muons.erase(it);
      if (it != processed_event -> muons . end()) it ++;

    } while(it != processed_event -> muons . end());
 
}



void Preselector::PreselectTaus() const
{
  pat::TauCollection::iterator it = processed_event -> taus . begin();
  do
    {
      bool passKin(true), passId(true);
      pat::Tau * tau = &*it;
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
	
      if(!passId || !passKin)          processed_event -> taus.erase(it);
      if (it != processed_event -> taus . end()) it ++;

    } while(it != processed_event -> taus . end());
}

void Preselector::PreselectJets() const
{
  pat::JetCollection::iterator it = processed_event -> jets.begin();
  do
    {
      pat::Jet * jet = &*it;
      bool passKin(true);
      if(jet -> pt() < 15 || fabs(jet -> eta()) > 4.7) passKin = false;
      if (passKin)
	{
	  //mc truth for this jet
	  const reco::GenJet* genJet = jet -> genJet();
	  TString jetType( genJet && genJet -> pt() > 0 ? "truejetsid" : "pujetsid" );

	  //cross-clean with selected leptons and photons
	  double minDRlj(9999.);
	  const size_t lepton_size[2] = {processed_event -> electrons.size(), processed_event -> muons.size()};
	  for (unsigned char type = 0; type < 2; type ++)
	    {
	      for(size_t ilep = 0; ilep < lepton_size[type]; ilep ++)
		{
		  minDRlj = TMath::Min(minDRlj, type == 0 ? deltaR(*jet, processed_event -> electrons[ilep]) : deltaR(*jet, processed_event -> muons[ilep]));
	  
		  if(minDRlj < 0.4) 
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
      
      if(!passKin || !passPFloose || !passLooseSimplePuId) processed_event -> jets.erase(it);
      if (it != processed_event -> jets.end()) it ++;
    }while (it != processed_event -> jets.end());
      
}

void Preselector::Report()
{
}

Preselector::~Preselector()
{
}
