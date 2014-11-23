#ifndef _EventConverter_hh
#define _EventConverter_hh
#include "LIP/TauAnalysis/interface/ReadEvent.hh"
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"

template<class InputEvent>
class EventConverter 
  :public EventProcessor<InputEvent, DigestedEvent*>
{

DigestedEvent* ConvertEvent(const InputEvent * const);

public:
  EventConverter(EventSink<DigestedEvent*> *next_processor_stage);
  void Run();
  void Report();
  virtual ~EventConverter();
};

template<>
DigestedEvent* EventConverter<ReadEvent_llvv>::ConvertEvent(const ReadEvent_llvv * const );

//#include "LIP/TauAnalysis/interface/templates/EventConverter_ReadEvent_llvv.cpp"
#endif
