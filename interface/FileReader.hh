#ifndef _FileReader_hh
#define _FileReader_hh
#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/LumiUtils.h"

class FileReader 
  :public EventProcessor<ReadEvent_llvv, ReadEvent_llvv> 
{
protected:
  lumiUtils::GoodLumiFilter *goodLumiFilter;  
public:
  FileReader(EventSink<ReadEvent_llvv> *next_processor_stage);
  void Run();
  void Report();
  virtual ~FileReader();
};
#endif
