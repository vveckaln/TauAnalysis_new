#ifndef _UncertaintiesApplicator_hh
#define _UncertaintiesApplicator_hh
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/HistogramPool.hh"
#include "LIP/TauAnalysis/interface/MuScleFitCorrector.h"

class UncertaintiesApplicator
  :public EventProcessor<DigestedEvent*, DigestedEvent *> 
{
  void ApplyJESuncertainty() const;
  DigestedEvent * processed_event;
  MuScleFitCorrector *muSCleFitCorrector; 
public:
  UncertaintiesApplicator(EventSink<DigestedEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~UncertaintiesApplicator();
};
#endif
