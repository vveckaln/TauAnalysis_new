#ifndef _PileUpCorrector_hh
#define _PileUpCorrector_hh
#include "TF1.h"
#include "CERN_RTU/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "CERN_RTU/TauAnalysis/interface/EventProcessor.hh"
#include "CERN_RTU/TauAnalysis/interface/Register.hh"

#include "CERN_RTU/TauAnalysis/interface/LeptonEfficiencySF.h"

#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "TGraph.h"

#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv * 

using namespace cpregister;
typedef vector<TGraph *> PuShifter_t;
enum PuShifterTypes {PUDOWN, PUUP};

class PileUpCorrector : public EventProcessor<event_type, event_type> 
{
  
  /*void getMCPileUpDistribution(
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
			      PuShifter_t PuShifters) const;*/

  unsigned long getMergeableCounterValue(const vector<string>& urls, const string counter) const;
  double                        XSectionWeight;
  edm::LumiReWeighting*         LumiWeights;
  double                        PUNorm[3];
  void ApplyLeptonEfficiencySF() const;
  void ApplyIntegratedLuminosity() const;
  void ApplyTopPtWeighter() const;
  LeptonEfficiencySF            leptonEfficiencySF;
  bool                          print_mode;
  
public:
  PileUpCorrector(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~PileUpCorrector();
protected:
  
};
#endif
