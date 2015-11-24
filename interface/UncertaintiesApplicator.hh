#ifndef _UncertaintiesApplicator_hh
#define _UncertaintiesApplicator_hh
#include "TauAnalysis/interface/DigestedEvent.hh"
#include "TauAnalysis/interface/EventProcessor.hh"
#include "TauAnalysis/interface/MuScleFitCorrector.h"
#include "TauAnalysis/interface/MacroUtils.h"

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
