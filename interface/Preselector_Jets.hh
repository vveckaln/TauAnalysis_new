#ifndef _Preselector_Jets_hh
#define _Preselector_Jets_hh
#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/SamplesCatalogue.hh"

#include "LIP/TauAnalysis/interface/test_utilities.hh"

#include "TH1F.h"
#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv * 

using namespace cpregister;
class Preselector_Jets : public EventProcessor<event_type, event_type> 
{
  bool print_mode;
  
  EventBuffer<event_type>::iterator it;
  unsigned int PreselectJets();
  
public:
  Preselector_Jets(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Preselector_Jets();

};
#endif