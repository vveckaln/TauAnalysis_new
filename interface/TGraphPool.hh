#ifndef _TGraphPool_hh
#define _TGraphPool_hh

#include "LIP/TauAnalysis/interface/ObjectPool.hh"
#include "LIP/TauAnalysis/interface/HistogramPool.hh"
#include <map>
#include "TGraph.h"
#include "TString.h"
#include "TFile.h"

using namespace std;

class TGraphPool: public ObjectPool<TGraph>
{
public:
  TGraphPool();
  void ConstructRatioGraphs(HistogramPool *, HistogramPool *);
  virtual ~ TGraphPool();
  
};
#endif
