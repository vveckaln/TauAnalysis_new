#ifndef _EventProcessor_hh
#define _EventProcessor_hh

#include "LIP/TauAnalysis/interface/EventSink.hh"
#include "LIP/TauAnalysis/interface/EventSource.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"

template<class TEventInput, class TEventOutput>
class EventProcessor:
  public EventSink<TEventInput>,
  public EventSource<TEventOutput>
{
public:
  EventProcessor(EventSink<TEventOutput> * sink);
  vector<HistogramDescriptor> * LoadHistogramDescriptors(const char*);
  virtual void Run();
  virtual void Report();
  virtual ~EventProcessor();
  
};
#include "LIP/TauAnalysis/interface/templates/EventProcessor.cpp"
#endif
