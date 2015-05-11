#ifndef _HistogramFiller_hh
#define _HistogramFiller_hh
#include "LIP/TauAnalysis/interface/PureEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"

class HistogramFiller 
  :public EventProcessor<PureEvent*, PureEvent *> 
{
public:
  double w {0};
  HistogramFiller(EventSink<PureEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~HistogramFiller();
protected:
  void FillHistograms();
};
#endif
