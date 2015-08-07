#ifndef _BTagger_hh
#define _BTagger_hh
#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TString.h"
#include <map>
//#include <utility>
using namespace std;
typedef ReadEvenv_llvv event_type;
class BTagger 
  :public EventProcessor<event_type, event_type> 
{
  ulong events_received;
  ulong events_btag_raised;
  ulong events_btag_lowered;
  bool activated;
  TFile *btag_file;
  map< pair<TString, TString>, pair<TGraphErrors*, TGraphErrors*> > btagEfficiencyCorrectionGraphs;
public:
  BTagger(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  ~BTagger();
};
#endif
