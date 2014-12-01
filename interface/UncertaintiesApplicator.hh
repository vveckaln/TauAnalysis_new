#ifndef _UncertaintiesApplicator_hh
#define _UncertaintiesApplicator_hh
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/HistogramPool.hh"
#include "LIP/TauAnalysis/interface/MuScleFitCorrector.h"
#include "LIP/TauAnalysis/interface/MacroUtils.h"

class UncertaintiesApplicator
  :public EventProcessor<DigestedEvent*, DigestedEvent *> 
{
  void ApplyJESuncertainty() const;
  DigestedEvent * processed_event;
  MuScleFitCorrector * muSCleFitCorrector; 
  FactorizedJetCorrector * factorizedJetCorrector;
  void ApplyMuScleFitCorrector() const;
  void ApplyFactorizedJetCorrector() const;
public:
  UncertaintiesApplicator(EventSink<DigestedEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~UncertaintiesApplicator();
};
#endif
