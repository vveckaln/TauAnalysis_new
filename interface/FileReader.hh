#ifndef _FileReader_hh
#define _FileReader_hh
#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/LumiUtils.h"
#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv * 

class FileReader 

  :public EventProcessor<event_type, event_type> 
{

protected:
  lumiUtils::GoodLumiFilter *goodLumiFilter;  
  unsigned long read;
  unsigned long muon_trigger;
  unsigned long goodLumiFilter_continue;
public:
  FileReader(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~FileReader();
};
//#undef event_type
#endif
