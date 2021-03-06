#ifndef _EventSink_hh
#define _EventSink_hh
#include "LIP/TauAnalysis/interface/EventBuffer.hh"
template<class TEventInput>
class EventSink{
public:
  EventBuffer<TEventInput>  *input_buffer;
  virtual void Run() = 0;
  virtual void Report() = 0;
  virtual ~EventSink(){
  }  
};
#endif
