#ifndef _EventSink_hh
#define _EventSink_hh
#include "CERN_RTU/TauAnalysis/interface/EventBuffer.hh"
template<class TEventInput>
class EventSink
{
public:
  EventBuffer<TEventInput>  *input_buffer;
  TEventInput input_event;
  virtual void Run() = 0;
  virtual void Report() = 0;
  virtual ~EventSink()
  {
  }  
};
#endif
