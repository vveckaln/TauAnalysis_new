#include "LIP/TauAnalysis/interface/FileReader.hh"
#include "LIP/TauAnalysis/interface/EventBuffer.hh"

#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/FWLite/interface/Handle.h"

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/PatUtils.h"

#include <iostream>
using namespace cpregister;
using namespace gVariables;

FileReader::FileReader(EventSink<event_type> * next_processor_stage):
EventProcessor<event_type, event_type>(next_processor_stage)
{
  goodLumiFilter  = new lumiUtils::GoodLumiFilter(luminosityBlockRange);

}

void FileReader::Run()
{
  //fwlite::ChainEvent  fwlite_ChainEvent (input_file_names);

  fwlite::ChainEvent & event = *fwlite_ChainEvent_ptr; 

  //printf("%lu\n", totalEntries);
  //getchar();
  //output_buffer = new EventBuffer<event_type>(10, "independent");
  const unsigned long totalEntries = event.size();
  printf("totalEntries = %lu\n", totalEntries);
  
  const uint division = 1;//gVariables::gDebug ? 40 : 1;
  for (unsigned long entry_ind = 0; entry_ind < totalEntries/division; entry_ind ++)
    {
      printf("entry %lu \n", entry_ind);
      ReadEvent_llvv Event;
      event_type read_event= &Event; //output_buffer -> GetWriteSlot(); 
      output_event = read_event;
      event.to(entry_ind);
      if (entry_ind % 10000 == 0)
	{
	  printf("Read %lu events\n", entry_ind);
	  //getchar();
	}
      read_event -> Run         = event.eventAuxiliary().run();
      read_event -> Lumi        = event.eventAuxiliary().luminosityBlock();
      read_event -> Event       = event.eventAuxiliary().event();
      edm::TriggerResultsByName tr = event.triggerResultsByName("HLT");

      read_event -> eeTrigger          = utils::passTriggerPatterns(tr, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*");
      read_event -> muTrigger          = utils::passTriggerPatterns(tr, "HLT_Mu34_TrkIsoVVL_v*");
      read_event -> mumuTrigger        = utils::passTriggerPatterns(tr, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*", "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*"); 
      read_event -> emuTrigger         = utils::passTriggerPatterns(tr, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*");
      if(!goodLumiFilter -> isGoodLumi(read_event -> Run, read_event -> Lumi))
	continue;
      fwlite::Handle< reco::VertexCollection > vtxHandle;
      vtxHandle.getByLabel(event, "offlineSlimmedPrimaryVertices");
      read_event -> vertices = *vtxHandle;

      fwlite::Handle< reco::GenParticleCollection > genHandle;
      genHandle.getByLabel(event, "prunedGenParticles");
      read_event -> genEv = *genHandle;

      fwlite::Handle< pat::MuonCollection > muonsHandle;
      muonsHandle.getByLabel(event, "slimmedMuons");
      if(muonsHandle.isValid()){ read_event -> muons = *muonsHandle;}

      fwlite::Handle< pat::ElectronCollection > electronsHandle;
      electronsHandle.getByLabel(event, "slimmedElectrons");
      if(electronsHandle.isValid()){ read_event -> electrons = *electronsHandle;}
      for (uint ind = 0; ind < read_event -> electrons.size(); ind ++)
	{
	  printf("superCluster eta %f \n", read_event -> electrons[ind]. superCluster() -> eta());
	}

      fwlite::Handle< pat::TauCollection > tausHandle;
      tausHandle.getByLabel(event, "slimmedTaus");
      if(tausHandle.isValid()){ read_event -> taus = *tausHandle;}

      for (unsigned int i = 0; i < read_event -> taus.size(); i++)
	{
	  printf("tau %u px = %f\n", i, read_event -> taus[i].px());
	}
      fwlite::Handle< pat::JetCollection > jetsHandle;
      jetsHandle.getByLabel(event, "slimmedJets");
      if(jetsHandle.isValid()){ read_event -> jets = *jetsHandle;}

      fwlite::Handle< pat::METCollection > metsHandle;
      metsHandle.getByLabel(event, "slimmedMETs");
      if(metsHandle.isValid()){ read_event -> MET = *metsHandle;}

      fwlite::Handle< double > rhoHandle;
      rhoHandle.getByLabel(event, "fixedGridRhoFastjetAll");
      if(rhoHandle.isValid()){ read_event -> rho = *rhoHandle;}
      
      fwlite::Handle< vector<PileupSummaryInfo> > puInfoH;
      puInfoH.getByLabel(event, "addPileupInfo");
      read_event  -> PU = *puInfoH;

      fwlite::Handle< GenEventInfoProduct > genEventInfoHandle;
      genEventInfoHandle.getByLabel(event, "generator");
      if(genEventInfoHandle.isValid()){ read_event -> genEventInfo = * genEventInfoHandle; }

      fwlite::Handle< pat::PhotonCollection > photonsHandle;
      photonsHandle.getByLabel(event, "slimmedPhotons");
      if(photonsHandle.isValid()){ read_event -> photons = *photonsHandle;}


      //output_buffer -> PushWriteSlot();

      //if (output_buffer -> IsFull())
      //	{
	  
	  

	      
	      for (uint ind = 0; ind < read_event -> electrons.size(); ind ++)
		{
		  printf("superCluster eta %f \n", read_event -> electrons[ind]. superCluster() -> eta());

		}
	    vector<pat::Electron*> el_vector;

	    vector<pat::Muon*> mu_vector;
  vector<pat::Electron*> * electrons_ptr; 
  vector<pat::Muon*> * muons_ptr;
  
  electrons_ptr = & el_vector;
  muons_ptr = & mu_vector;
  electrons_ptr -> clear();
  muons_ptr -> clear();
  ReadEvent_llvv * it = read_event;
  printf("event at reader %p %p\n", it, output_event);
  for (size_t ind = 0; ind < it -> electrons.size(); ind ++) 
	{
	  electrons_ptr -> push_back(&it -> electrons[ind]);
	  printf("%lu electron %p\n", ind, & it -> electrons[ind]);
	  ind ++;
	}
	  getchar();
	  ProceedToNextStage();
	  printf("deleting output_buffer %p\n", output_buffer);
	  //delete output_buffer;
	  printf("Deleted\n");
	  // output_buffer = NULL;
	  //output_buffer = new EventBuffer<event_type>(10, "independent");
	  //}

    } 
/*if (output_buffer != NULL)
    {
      if (!output_buffer -> IsEmpty())
	{
	  ProceedToNextStage();
	  delete output_buffer;
	}
	}*/
  
}
 
void FileReader::Report()
{
  ContinueReportToNextStage();
}


FileReader::~FileReader()
{
  delete goodLumiFilter;
}
