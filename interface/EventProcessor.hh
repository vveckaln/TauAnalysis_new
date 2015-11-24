#ifndef _EventProcessor_hh
#define _EventProcessor_hh

#include "CERN_RTU/TauAnalysis/interface/EventSink.hh"
#include "CERN_RTU/TauAnalysis/interface/EventSource.hh"
#include "CERN_RTU/TauAnalysis/interface/Register.hh"
#include "CERN_RTU/TauAnalysis/interface/HistogramDescriptor.hh"

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
#include "CERN_RTU/TauAnalysis/interface/templates/EventProcessor.cpp"
#endif
