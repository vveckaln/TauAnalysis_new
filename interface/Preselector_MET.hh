#ifndef _Preselector_MET_hh
#define _Preselector_MET_hh
#include "CERN_RTU/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "CERN_RTU/TauAnalysis/interface/EventProcessor.hh"
#include "CERN_RTU/TauAnalysis/interface/Register.hh"
#include "CERN_RTU/TauAnalysis/interface/SamplesCatalogue.hh"

#include "CERN_RTU/TauAnalysis/interface/test_utilities.hh"

#include "TH1F.h"
using namespace cpregister;
#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv *
class Preselector_MET : public EventProcessor<event_type, event_type> 
{
  bool print_mode;
  double selected;
  double selected2;
  event_type * processed_event;
  EventBuffer<event_type>::iterator it;
  
public:
  Preselector_MET(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Preselector_MET();

};
#endif
