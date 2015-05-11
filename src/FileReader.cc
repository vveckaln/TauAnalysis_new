#include "LIP/TauAnalysis/interface/FileReader.hh"
#include "LIP/TauAnalysis/interface/EventBuffer.hh"
#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "LIP/TauAnalysis/interface/MacroUtils.h"

#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


#include <iostream>
using namespace cpFileRegister;
using namespace cpHistogramPoolRegister;

FileReader::FileReader(EventSink<ReadEvent_llvv> * next_processor_stage):
EventProcessor<ReadEvent_llvv, ReadEvent_llvv>(next_processor_stage)
{
  duplicates_checker = new DuplicatesChecker;
  number_duplicates = 0;
}

void FileReader::Run()
{
  //fwlite::ChainEvent  fwlite_ChainEvent (input_file_names);

  fwlite::ChainEvent & fwlite_ChainEvent = *fwlite_ChainEvent_ptr; 

  //printf("%lu\n", totalEntries);
  //getchar();
  output_buffer = new EventBuffer<ReadEvent_llvv>(10);
  const unsigned long totalEntries = fwlite_ChainEvent.size();
  const uint division = gVariables::gDebug ? 40 : 1;
  for (unsigned long entry_ind = 0; entry_ind < totalEntries/division; entry_ind ++)
    {
      ReadEvent_llvv read_event;// = output_buffer -> GetWriteSlot(); 
      fwlite_ChainEvent.to(entry_ind);
      if (entry_ind % 10000 == 0)
	{
	  printf("Read %lu events\n", entry_ind);
	  //getchar();
	}
      if (gIsData and duplicates_checker -> 
	  isDuplicate( 
		   fwlite_ChainEvent.eventAuxiliary().run(),
		   fwlite_ChainEvent.eventAuxiliary().luminosityBlock(),
		   fwlite_ChainEvent.eventAuxiliary().event()))
	{
	  number_duplicates ++;
	  continue;
	}

      fwlite::Handle< llvvGenEvent > genEventHandle;
      genEventHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed");
      if(!genEventHandle.isValid()){printf("llvvGenEvent Object NotFound\n");continue;}
      read_event.genEv = *genEventHandle;

      fwlite::Handle< llvvLeptonCollection > leptonCollHandle;
      leptonCollHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed");
      if(!leptonCollHandle.isValid()){printf("llvvLeptonCollection Object NotFound\n");continue;}
      read_event.leptons = *leptonCollHandle;

      fwlite::Handle< llvvJetCollection > jetCollHandle;
      jetCollHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed");
      if(!jetCollHandle.isValid()){printf("llvvJetCollection Object NotFound\n");continue;}
      
      for(unsigned int jet_ind = 0; jet_ind < jetCollHandle ->size(); jet_ind ++)
	{

	  read_event.jets.push_back(llvvJetExt((*jetCollHandle)[jet_ind]));

	}
     
      fwlite::Handle< llvvMet > metHandle;
      metHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed", "pfType1CorrectedMet");
      if(!metHandle.isValid()){printf("llvvMet Object NotFound\n");continue;}
      read_event.met = *metHandle;

      fwlite::Handle< llvvTauCollection > tauCollHandle;
      tauCollHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed");
      read_event.taus = *tauCollHandle;   
      for (unsigned int ind = 0; ind < (*tauCollHandle).size(); ind ++)
	{
	  printf("size %lu %lu\n", read_event.taus[ind].tracks.size(), (*tauCollHandle)[ind].tracks.size() );
	}
      fwlite::Handle< double > rhoHandle;
      rhoHandle.getByLabel(fwlite_ChainEvent, "kt6PFJets", "rho");
      if(!rhoHandle.isValid()){printf("rho Object NotFound\n");continue;}
      read_event.rho = *rhoHandle;
      for (unsigned int lepton_ind = 0; lepton_ind < read_event . leptons.size(); lepton_ind ++)
	{
	 
	  if (abs(read_event.leptons[lepton_ind].id) ==11)
	    {
	      read_event.leptons[lepton_ind].el_info    = *read_event.leptons[lepton_ind].electronInfoRef.get();
	      /*printf("IsConv %s %s\n", read_event . leptons[lepton_ind].el_info.isConv ? "true" : "false", read_event . leptons[lepton_ind].electronInfoRef->isConv ? "true" : "false");
	      printf("mvatrigv0 %f %f\n", read_event . leptons[lepton_ind].el_info.mvatrigv0, read_event . leptons[lepton_ind].electronInfoRef->mvatrigv0);
	      printf("sceta %f %f\n",  read_event . leptons[lepton_ind].el_info.sceta,        read_event. leptons[lepton_ind].electronInfoRef->sceta);*/
	    }
	}
      
      fwlite::Handle< vector<bool> > triggerBitsHandle;
      triggerBitsHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed", "triggerBits");
      if(!triggerBitsHandle.isValid()){printf("triggerBits Object NotFound\n");continue;}
      read_event.triggerBits = *triggerBitsHandle;

      fwlite::Handle< llvvGenParticleCollection > genPartCollHandle;
      genPartCollHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed");
      if(!genPartCollHandle.isValid()){printf("llvvGenParticleCollection Object NotFound\n");continue;}
      read_event.gen = *genPartCollHandle;
      /*printf("%lu %lu\n", read_event.gen.size(), genPartCollHandle -> size());
      for (unsigned long ind = 0; ind < genPartCollHandle -> size(); ind ++)
	{
	  const reco::GenParticle & p = (*genPartCollHandle)[ind];
	  printf("daughters %lu\n", p.numberOfDaughters());
	}
	getchar();*/
      read_event.Run         = fwlite_ChainEvent.eventAuxiliary().run();
      read_event.Lumi        = fwlite_ChainEvent.eventAuxiliary().luminosityBlock();
      read_event.Event       = fwlite_ChainEvent.eventAuxiliary().event();

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
  printf("number of duplicates %lu\n", number_duplicates); 
  ContinueReportToNextStage();
}


FileReader::~FileReader()
{
  delete duplicates_checker;
}
