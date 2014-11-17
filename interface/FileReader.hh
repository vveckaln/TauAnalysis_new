#ifndef _FileReader_hh
#define _FileReader_hh
#include "LIP/TauAnalysis/interface/ReadEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"

class FileReader 
  :public EventProcessor<ReadEvent, ReadEvent> 
{
public:
  FileReader(EventSink<ReadEvent> *next_processor_stage);
  void Run();
  void Report();
  virtual ~FileReader();
};
#endif
