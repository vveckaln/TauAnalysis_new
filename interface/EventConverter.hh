#ifndef _EventConverter_hh
#define _EventConverter_hh
#include "CERN_RTU/TauAnalysis/interface/ReadEvent.hh"
#include "CERN_RTU/TauAnalysis/interface/DigestedEvent.hh"
#include "CERN_RTU/TauAnalysis/interface/EventProcessor.hh"

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

//#include "CERN_RTU/TauAnalysis/interface/templates/EventConverter_ReadEvent_llvv.cpp"
#endif
