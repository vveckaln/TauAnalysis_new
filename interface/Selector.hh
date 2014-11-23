#ifndef _Selector_hh
#define _Selector_hh
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/PureEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
using namespace cpHistogramPoolRegister;

class Selector : public EventProcessor<DigestedEvent*, PureEvent*> 
{
  bool LeptonValid;
  bool LooseLeptonValid;
  bool JetValid;
  bool BtagValid;
  bool METValid;
  bool TausValid;
  bool TauOS;
  DigestedEvent * processed_event;
  mutable PureEvent pure_event;
  mutable Lepton *lepton;
  void ChannelGate() const;
  bool CheckTrigger() const;
  bool IsLowQualityEvent() const;
  void SelectorStatistics();
  bool ValidateElectron() const;
  bool ValidateMuon() const;
  bool ValidateLooseLepton() const;
  bool ValidateBtag() const;
  bool ValidateTaus() const;
  bool ValidateTauOS() const;
  bool ValidateJets() const;
  inline  bool ValidateMET() const;
  bool ValidateEvent();
  bool DeleteHadronisedTauJet() const;
  void RunInTestMode();
  void FinishPureEvent();
public:
  Selector(EventSink<PureEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Selector();

};
#endif
