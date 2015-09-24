#ifndef _Preselector_Taus_hh
#define _Preselector_Taus_hh
#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/SamplesCatalogue.hh"

#include "LIP/TauAnalysis/interface/test_utilities.hh"

#include "TH1F.h"
using namespace cpregister;
#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv *
class Preselector_Taus : public EventProcessor<event_type, event_type> 
{
  bool print_mode;
  double selected;
  event_type * processed_event;
  EventBuffer<event_type>::iterator it;
  unsigned int PreselectTaus() ;
  void Order_Taus();
public:
  Preselector_Taus(EventSink<event_type> *next_processor_stage);
  
  void Run();
  void Report();
  virtual ~Preselector_Taus();

};
#endif
