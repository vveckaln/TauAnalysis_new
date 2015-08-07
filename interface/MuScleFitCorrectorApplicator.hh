#ifndef _MuScleFitCorrectorApplicator_hh
#define _MuScleFiteCorrectorApplicator_hh
#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/MuScleFitCorrector.h"

class MuScleFitCorrectorApplicator
  :public EventProcessor<ReadEvent_llvv, ReadEvent_llvv> 
{
  ReadEvent_llvv * processed_event;
  MuScleFitCorrector * muSCleFitCorrector; 
  void ApplyMuScleFitCorrector() const;
public:
  MuScleFitCorrectorApplicator(EventSink<ReadEvent_llvv> *next_processor_stage);
  void Run();
  void Report();
  virtual ~MuScleFitCorrectorApplicator();
};
#endif
