#ifndef _MuScleFitCorrectorApplicator_hh
#define _MuScleFiteCorrectorApplicator_hh
#include "CERN_RTU/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "CERN_RTU/TauAnalysis/interface/EventProcessor.hh"
#include "CERN_RTU/TauAnalysis/interface/MuScleFitCorrector.h"
#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv * 

class MuScleFitCorrectorApplicator
  :public EventProcessor<event_type, event_type> 
{
  event_type * processed_event;
  MuScleFitCorrector * muSCleFitCorrector; 
  void ApplyMuScleFitCorrector() const;
public:
  MuScleFitCorrectorApplicator(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~MuScleFitCorrectorApplicator();
};
#endif
