#ifndef _PileUpCorrector_hh
#define _PileUpCorrector_hh
#include "TF1.h"
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"

#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "TGraph.h"

using namespace cpHistogramPoolRegister;
using namespace cpFileRegister;
typedef vector<TGraph *> PuShifter_t;
enum PuShifterTypes {PUDOWN, PUUP};

class PileUpCorrector : public EventProcessor<DigestedEvent*, DigestedEvent*> 
{
  DigestedEvent * processed_event;
  void getMCPileUpDistribution(
			       fwlite::ChainEvent&, 
			       const unsigned int Npu, 
			       vector<float> &);
  PuShifter_t getPUshifters(
			    vector<float> &Lumi_distr,
			    const float puUnc) const;
  void getPileUpNormalization(
			      vector<float>& MCPileUp, 
			      double* PUNorm, 
			      edm::LumiReWeighting* LumiWeights, 
			      PuShifter_t PuShifters) const;

  unsigned long getMergeableCounterValue(const vector<string>& urls, const string counter) const;
  double XSectionWeight;
  edm::LumiReWeighting* LumiWeights[2];
  double PUNorm[2][3];

public:
  PileUpCorrector(EventSink<DigestedEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~PileUpCorrector();
protected:
  
};
#endif
