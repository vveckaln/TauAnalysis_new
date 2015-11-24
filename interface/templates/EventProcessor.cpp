#include "CERN_RTU/TauAnalysis/interface/Parser.hh"


template<class TEventInput, class TEventOutput>
EventProcessor<TEventInput, TEventOutput>::EventProcessor(EventSink<TEventOutput> *sink): EventSource<TEventOutput>(sink)
{

}

template<class TEventInput, class TEventOutput>
void EventProcessor<TEventInput, TEventOutput>::Run()
{
  
}



template<class TEventInput, class TEventOutput>
void EventProcessor<TEventInput, TEventOutput>::Report()
{
}

template<class TEventInput, class TEventOutput>
EventProcessor<TEventInput, TEventOutput>::~EventProcessor()
{
}

template<class TEventInput, class TEventOutput>
vector<HistogramDescriptor> * EventProcessor<TEventInput, TEventOutput>::LoadHistogramDescriptors(const char* specifier)
{
  Parser *parser = new Parser();
  vector<HistogramDescriptor> * descriptor = parser -> ParseHistogramSpecifier(specifier);
  delete parser;
  return descriptor;
}

/*template<class TEventInput, class TEventOutput>
void EventProcessor<TEventInput, TEventOutput>::ProceedToNextStage(){
     if (next_processor_stage != 0){
     	next_processor_stage -> input_buffer = output_buffer;
     	next_processor_stage -> Run();
     }
}*/
