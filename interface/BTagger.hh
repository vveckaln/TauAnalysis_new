#ifndef _BTagger_hh
#define _BTagger_hh
#include "TauAnalysis/interface/ReadEvent_llvv.hh"
#include "TauAnalysis/interface/EventProcessor.hh"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TString.h"
#include <map>
//#include <utility>
#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv *

using namespace std;

class BTagger 
  :public EventProcessor<event_type, event_type> 
{
  ulong events_received;
  ulong events_btag_raised;
  ulong events_btag_lowered;
  double selected;
  bool activated;
  TFile *btag_file;
  map< pair<TString, TString>, pair<TGraphErrors*, TGraphErrors*> > btagEfficiencyCorrectionGraphs;
public:
  BTagger(EventSink<event_type> *next_processor_stage);

  void Run();
  void Report();
  ~BTagger();
};

//#undef event_type
#endif
