#include "LIP/TauAnalysis/interface/FileReader.hh"
#include "LIP/TauAnalysis/interface/EventBuffer.hh"
#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "LIP/TauAnalysis/interface/MacroUtils.h"

#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/FWLite/interface/Handle.h"

#include <iostream>
using namespace cpFileRegister;
using namespace cpHistogramPoolRegister;

FileReader::FileReader(EventSink<ReadEvent_llvv> * next_processor_stage):
EventProcessor<ReadEvent_llvv, ReadEvent_llvv>(next_processor_stage)
{
  duplicates_checker = new DuplicatesChecker;
}

void FileReader::Run()
{
  //fwlite::ChainEvent  fwlite_ChainEvent (input_file_names);

  fwlite::ChainEvent & fwlite_ChainEvent = *fwlite_ChainEvent_ptr; 

  const unsigned long totalEntries = fwlite_ChainEvent.size();
  //printf("%lu\n", totalEntries);
  //getchar();
  output_buffer = new EventBuffer<ReadEvent_llvv>(10);
  const uint division = 20;
  for (unsigned long entry_ind = 0; entry_ind < totalEntries/division; entry_ind ++)
    {
      ReadEvent_llvv read_event;// = output_buffer -> GetWriteSlot(); 
      fwlite_ChainEvent.to(entry_ind);
      if (entry_ind % 10000 == 0)
	{
	  printf("Read %lu events\n", entry_ind);
	  //getchar();
	}
      if (isData and duplicates_checker -> 
	  isDuplicate( 
		   fwlite_ChainEvent.eventAuxiliary().run(),
		   fwlite_ChainEvent.eventAuxiliary().luminosityBlock(),
		   fwlite_ChainEvent.eventAuxiliary().event()))
	{
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
      
      for(unsigned int i = 0; i < jetCollHandle ->size();i++)
	{
	  read_event.jets.push_back(llvvJetExt((*jetCollHandle)[i]));
	}
     
      fwlite::Handle< llvvMet > metHandle;
      metHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed", "pfType1CorrectedMet");
      if(!metHandle.isValid()){printf("llvvMet Object NotFound\n");continue;}
      read_event.met = *metHandle;

      fwlite::Handle< llvvTauCollection > tauCollHandle;
      tauCollHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed");
      read_event.taus = *tauCollHandle;   

      fwlite::Handle< double > rhoHandle;
      rhoHandle.getByLabel(fwlite_ChainEvent, "kt6PFJets", "rho");
      if(!rhoHandle.isValid()){printf("rho Object NotFound\n");continue;}
      read_event.rho = *rhoHandle;
      for (unsigned int lepton_ind = 0; lepton_ind < read_event . leptons.size(); lepton_ind ++)
	{
	 
	  if (abs(read_event.leptons[lepton_ind].id) ==11)
	    {
	      read_event.leptons[lepton_ind].el_info = * read_event.leptons[lepton_ind].electronInfoRef.get();
	      
	    }
	}
      
      
      fwlite::Handle< vector<bool> > triggerBitsHandle;
      triggerBitsHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed", "triggerBits");
      if(!triggerBitsHandle.isValid()){printf("triggerBits Object NotFound\n");continue;}
      read_event.triggerBits = *triggerBitsHandle;

      
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
  delete duplicates_checker;
}
