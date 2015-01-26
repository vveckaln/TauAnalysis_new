#ifndef _ChannelGate_hh
#define _ChannelGate_hh
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/PureEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
#include "LIP/TauAnalysis/interface/LeptonEfficiencySF.h"
#include "TH1F.h"
using namespace cpHistogramPoolRegister;

class ChannelGate : public EventProcessor<DigestedEvent*, DigestedEvent*> 
{
  bool PassedCleaning;
  bool LeptonCorresponds;
  bool Trigger_Fired;
  static const short report_size;
  static const char *ChannelGate_report_Xaxis_labels[]; 
  DigestedEvent * processed_event;
  bool IsLowQualityEvent() const;
  bool CheckLeadingLepton() const;
  bool TriggerFired() const;
  void CollectStatistics();
  bool ChannelOpened();
  TH1D * const GetStatisticsHistogram();
public:
  ChannelGate(EventSink<DigestedEvent *> *next_processor_stage);
  void Run();
  void Report();
  virtual ~ChannelGate();

};
#endif
