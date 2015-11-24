#ifndef _UncertaintiesApplicator_hh
#define _UncertaintiesApplicator_hh
#include "CERN_RTU/TauAnalysis/interface/DigestedEvent.hh"
#include "CERN_RTU/TauAnalysis/interface/EventProcessor.hh"
#include "CERN_RTU/TauAnalysis/interface/MuScleFitCorrector.h"
#include "CERN_RTU/TauAnalysis/interface/MacroUtils.h"

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
