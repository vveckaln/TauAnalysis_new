#ifndef _FactorisedJetCorrectorApplicator_hh
#define _FactorisedJetCorrectorApplicator_hh
#include "TauAnalysis/interface/ReadEvent_llvv.hh"
#include "TauAnalysis/interface/EventProcessor.hh"
#include "TauAnalysis/interface/MacroUtils.h"

typedef ReadEvent_llvv event_type;

class FactorisedJetCorrectorApplicator
  :public EventProcessor<event_type, event_type> 
{
  void ApplyJESuncertainty() const;
  event_type * processed_event;
  FactorizedJetCorrector * factorizedJetCorrector;
  void ApplyFactorizedJetCorrector() const;
public:
  FactorisedJetCorrectorApplicator(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~FactorisedJetCorrectorApplicator();
};
#endif
