#ifndef _BTagger_hh
#define _BTagger_hh
#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/EventProcessor.hh"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TString.h"
#include <map>
//#include <utility>
using namespace std;
class BTagger 
  :public EventProcessor<DigestedEvent*, DigestedEvent*> 
{
  bool activated;
  TFile *btag_file;
  map< pair<TString, TString>, pair<TGraphErrors*, TGraphErrors*> > btagEfficiencyCorrectionGraphs;
public:
  BTagger(EventSink<DigestedEvent*> *next_processor_stage);
  void Run();
  void Report();
  ~BTagger();
};
#endif
