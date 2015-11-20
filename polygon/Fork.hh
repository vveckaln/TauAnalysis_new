#ifndef _Fork_hh
#define _Fork_hh
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
using namespace cpHistogramPoolRegister;

class Fork : public EventProcessor<DigestedEvent*, DigestedEvent*> 
{
public:
  Fork(EventSink<DigestedEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Fork();
};
#endif
