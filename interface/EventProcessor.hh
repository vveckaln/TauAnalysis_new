#ifndef _EventProcessor_hh
#define _EventProcessor_hh

#include "LIP/TauAnalysis/interface/EventSink.hh"
#include "LIP/TauAnalysis/interface/EventSource.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
template<class TEventInput, class TEventOutput>
class EventProcessor:
  public EventSink<TEventInput>,
  public EventSource<TEventOutput>
 {
public:
  EventProcessor(EventSink<TEventOutput> * sink);
  virtual void Run();
  virtual void Report();
  virtual ~EventProcessor();
  
};
#include "LIP/TauAnalysis/interface/templates/EventProcessor.tpp"
#endif
