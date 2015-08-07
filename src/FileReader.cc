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

#include <iostream>
using namespace cpregister;
using namespace gVariables;

FileReader::FileReader(EventSink<ReadEvent_llvv> * next_processor_stage):
EventProcessor<ReadEvent_llvv, ReadEvent_llvv>(next_processor_stage)
{
  goodLumiFilter  = new lumiUtils::GoodLumiFilter(luminosityBlockRange);

}

void FileReader::Run()
{
  //fwlite::ChainEvent  fwlite_ChainEvent (input_file_names);

  fwlite::ChainEvent & fwlite_ChainEvent = *fwlite_ChainEvent_ptr; 

  //printf("%lu\n", totalEntries);
  //getchar();
  output_buffer = new EventBuffer<ReadEvent_llvv>(10);
  const unsigned long totalEntries = fwlite_ChainEvent.size();
  printf("totalEntries = %lu\n", totalEntries);
  
  const uint division = gVariables::gDebug ? 40 : 1;
  for (unsigned long entry_ind = 0; entry_ind < totalEntries/division; entry_ind ++)
    {
      printf("entry %lu \n", entry_ind);
      ReadEvent_llvv read_event;// = output_buffer -> GetWriteSlot(); 
      fwlite_ChainEvent.to(entry_ind);
      if (entry_ind % 10000 == 0)
	{
	  printf("Read %lu events\n", entry_ind);
	  //getchar();
	}
      read_event.Run         = fwlite_ChainEvent.eventAuxiliary().run();
      read_event.Lumi        = fwlite_ChainEvent.eventAuxiliary().luminosityBlock();
      read_event.Event       = fwlite_ChainEvent.eventAuxiliary().event();

      if(!goodLumiFilter -> isGoodLumi(read_event.Run, read_event.Lumi))
	continue;
      fwlite::Handle< reco::VertexCollection > vtxHandle;
      vtxHandle.getByLabel(fwlite_ChainEvent, "offlineSlimmedPrimaryVertices");
      read_event.vertices = *vtxHandle;

      fwlite::Handle< reco::GenParticleCollection > genHandle;
      genHandle.getByLabel(fwlite_ChainEvent, "prunedGenParticles");
      read_event.genEv = *genHandle;

      fwlite::Handle< pat::MuonCollection > muonsHandle;
      muonsHandle.getByLabel(fwlite_ChainEvent, "slimmedMuons");
      if(muonsHandle.isValid()){ read_event.muons = *muonsHandle;}

      fwlite::Handle< pat::ElectronCollection > electronsHandle;
      electronsHandle.getByLabel(fwlite_ChainEvent, "slimmedElectrons");
      if(electronsHandle.isValid()){ read_event.electrons = *electronsHandle;}

      fwlite::Handle< pat::TauCollection > tausHandle;
      tausHandle.getByLabel(fwlite_ChainEvent, "slimmedTaus");
      if(tausHandle.isValid()){ read_event.taus = *tausHandle;}

      for (unsigned int i = 0; i < read_event.taus.size(); i++)
	{
	  printf("tau %u px = %f\n", i, read_event.taus[i].px());
	}
      fwlite::Handle< pat::JetCollection > jetsHandle;
      jetsHandle.getByLabel(fwlite_ChainEvent, "slimmedJets");
      if(jetsHandle.isValid()){ read_event.jets = *jetsHandle;}

      fwlite::Handle< pat::METCollection > metsHandle;
      metsHandle.getByLabel(fwlite_ChainEvent, "slimmedMETs");
      if(metsHandle.isValid()){ read_event.MET = *metsHandle;}

      fwlite::Handle< double > rhoHandle;
      rhoHandle.getByLabel(fwlite_ChainEvent, "fixedGridRhoFastjetAll");
      if(rhoHandle.isValid()){ read_event.rho = *rhoHandle;}
      
      fwlite::Handle< vector<PileupSummaryInfo> > puInfoH;
      puInfoH.getByLabel(fwlite_ChainEvent, "addPileupInfo");
      read_event.PU = *puInfoH;

      fwlite::Handle< GenEventInfoProduct > genEventInfoHandle;
      genEventInfoHandle.getByLabel(fwlite_ChainEvent, "generator");
      if(genEventInfoHandle.isValid()){ read_event.genEventInfo = * genEventInfoHandle; }

      output_buffer -> GetWriteSlot() = read_event;
      output_buffer -> PushWriteSlot();

      if (output_buffer -> IsFull())
	{
	  ProceedToNextStage();
	  delete output_buffer;
	  output_buffer = NULL;
	  output_buffer = new EventBuffer<ReadEvent_llvv>(10);
	}

    } 
  if (output_buffer != NULL)
    {
      if (!output_buffer -> IsEmpty())
	{
	  ProceedToNextStage();
	  delete output_buffer;
	}
    }
  
}
 
void FileReader::Report()
{
  ContinueReportToNextStage();
}


FileReader::~FileReader()
{
  delete goodLumiFilter;
}
