#ifndef _Selector_hh
#define _Selector_hh
#include "TauAnalysis/interface/DigestedEvent.hh"
#include "TauAnalysis/interface/PureEvent.hh"
#include "TauAnalysis/interface/EventProcessor.hh"
#include "TauAnalysis/interface/Register.hh"
#include "TauAnalysis/interface/SamplesCatalogue.hh"

#include "TauAnalysis/interface/test_utilities.hh"

#include "TH1F.h"
using namespace cpregister;

class Selector : public EventProcessor<DigestedEvent*, PureEvent*> 
{
  bool LeptonValid;
  bool LooseLeptonValid;
  bool JetValid;
  bool BtagValid;
  bool METValid;
  bool TausValid;
  bool TauOS;
  bool print_mode;
  static const short report_size;
  static const char *Selector_report_Xaxis_labels[]; 
  DigestedEvent * processed_event;
  mutable PureEvent pure_event;
  mutable Lepton *lepton;
  mutable vector<Jet> validated_jets;
  void Reset();
  void CollectStatistics();
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
  TH1D * const GetStatisticsHistogram(const unsigned short);
  mutable unsigned short nVeto_electrons;
  mutable unsigned short nVeto_muons;
public:
  Selector(EventSink<PureEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Selector();

};
#endif
