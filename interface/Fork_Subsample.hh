#ifndef _Fork_Subsample_hh
#define _Fork_Subsample_hh
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/PureEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"

#include "LIP/TauAnalysis/interface/SamplesCatalogue.hh"
#include "LIP/TauAnalysis/interface/LeptonEfficiencySF.h"
#include "TH1F.h"
#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv * 

using namespace cpregister;

class Fork_Subsample : public EventProcessor<event_type, event_type> 
{
  double received;
  double passed;
  bool valid_TTbarMC;
  unsigned char ngen_electron, ngen_muon, ngen_tau, ngen_quark;
  
  EventBuffer<event_type>::iterator it;
  bool (Fork_Subsample::**sample_check_ptr)() const;
  bool CheckTTbarMC_muon_tau() const;
  bool CheckTTbarMC_lepton_jets() const;
  bool CheckTTbarMC_dilepton_muon_electron() const;
  bool CheckTTbarMC_dilepton_muon_muon() const;
  bool CheckTTbarMC_tau_jets() const;
  bool CheckTTbarMC_tau_tau() const;
  bool CheckTTbarMC_hadronic() const;

  bool CheckDY_lepton_lepton() const;
  bool CheckDY_tau_tau() const;
  bool CheckWJets() const;
  bool CheckGeneric() const;

  void SetEnvironment_TTbarMC();
  void SetEnvironment_DY();
  void SetEnvironment_tW();
  void SetEnvironment_WJets();
  void SetEnvironment_generic();
  void CountLeptons_TTbarMC();
  void CountLeptons_WJets();
  void CountLeptons_DY();
  void CollectStatistics();
public:
  Fork_Subsample(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Fork_Subsample();

};
#endif
