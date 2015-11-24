#ifndef _Fork_hh
#define _Fork_hh
#include "TauAnalysis/interface/DigestedEvent.hh"
#include "TauAnalysis/interface/EventProcessor.hh"
#include "TauAnalysis/interface/Register.hh"
using namespace cpregister;

class Fork : public EventProcessor<DigestedEvent*, DigestedEvent*> 
{
public:
  Fork(EventSink<DigestedEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Fork();
};
#endif
