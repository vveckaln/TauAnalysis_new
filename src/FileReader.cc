#include "LIP/TauAnalysis/interface/FileReader.hh"
#include "LIP/TauAnalysis/interface/EventBuffer.hh"
#include "LIP/TauAnalysis/interface/ReadEvent.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
#include "LIP/TauAnalysis/interface/llvvObjects.h"

#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/FWLite/interface/Handle.h"

#include <iostream>
using namespace cpFileRegister;

FileReader::FileReader(EventSink<ReadEvent> * next_processor_stage):EventProcessor<ReadEvent, ReadEvent>(next_processor_stage)
{
}

void FileReader::Run()
{
  fwlite::ChainEvent  fwlite_ChainEvent (input_file_names);
  const unsigned long totalEntries = fwlite_ChainEvent.size();
  
/*TTree *read_tree = (TTree*) input_file -> Get("myEventSelector/data");
  ReadEvent read_event = ReadEvent();
  read_event . Open();
  read_event . ConnectToTree(read_tree);
  output_buffer = new EventBuffer<ReadEvent>(10);*/
  for (unsigned long entry_ind = 0; entry_ind < totalEntries; entry_ind ++)
    {
      fwlite_ChainEvent.to(entry_ind);
      if (entry_ind % 1000 == 0) printf("Read %lu events\n", entry_ind);
      fwlite::Handle< llvvTauCollection > tauCollHandle;
      tauCollHandle.getByLabel(fwlite_ChainEvent, "llvvObjectProducersUsed");
      llvvTauCollection taus = *tauCollHandle;   
      for(size_t itau = 0; itau < taus.size(); itau++)
	{
	  llvvTau& tau = taus[itau];
	  printf("%f\n", tau.Pt());
	} 
      getchar();
      /* output_buffer -> PushWriteSlot();
        
    if (output_buffer -> IsFull()){
    
      ProceedToNextStage();
      delete output_buffer;
      output_buffer = new EventBuffer<ReadEvent>(10);
      }*/

    } 
  /*if (!output_buffer -> IsEmpty()){
    ProceedToNextStage();
    delete output_buffer;
  }
  read_event . Close();*/
}
 
void FileReader::Report()
{
  ContinueReportToNextStage();
}


FileReader::~FileReader(){
}
