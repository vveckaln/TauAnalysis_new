#ifndef _ChannelGate_hh
#define _ChannelGate_hh
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

class ChannelGate : public EventProcessor<event_type, event_type> 
{
  bool PassedCleaning;
  bool LeptonCorresponds;
  bool Trigger_Fired;
  bool OtherTriggersVeto;
  bool valid_TTbarMC;
  static const short report_size;
  static const char *ChannelGate_report_Xaxis_labels[]; 
  EventBuffer<event_type>::iterator it;
  bool IsLowQualityEvent() const;
  bool CheckLeadingLepton() ;
  bool TriggerFired() ;
  bool VetoAdditionalTriggers() ;
  bool (ChannelGate::**sample_check_ptr)() const;
  bool CheckTTbarMC_muon_tau() const;
  bool CheckTTbarMC_lepton_jets() const;
  bool CheckTTbarMC_dilepton_muon_electron() const;
  bool CheckTTbarMC_dilepton_muon_muon() const;
  bool CheckTTbarMC_tau_jets() const;
  bool CheckTTbarMC_tau_tau() const;
  bool CheckTTbarMC_hadronic() const;

  bool CheckDY_lepton_lepton() const;
  bool CheckDY_tau_tau() const;

  bool CheckGeneric() const;

  void SetEnvironment_TTbarMC();
  void SetEnvironment_DY();
  void SetEnvironment_tW();
  void SetEnvironment_generic();

  void CollectStatistics();
  bool ChannelOpened();
  inline TH1D * const GetStatisticsHistogram(const unsigned short) const;
public:
  ChannelGate(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~ChannelGate();

};
#endif
