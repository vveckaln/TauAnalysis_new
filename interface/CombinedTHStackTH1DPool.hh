#ifndef _CombinedTHStackTH1DPool_hh
#define _CombinedTHStackTH1DPool_hh

#include "LIP/TauAnalysis/interface/CombinedTHStackTH1D.hh"
#include "LIP/TauAnalysis/interface/ObjectPool.hh"

using namespace std;

class CombinedTHStackTH1DPool: public ObjectPool<CombinedTHStackTH1D> 
{
public:
  CombinedTHStackTH1DPool();
  void AddObjects(const vector<HistogramDescriptor> *, const char * = "");
  void Process();
  virtual ~ CombinedTHStackTH1DPool();
  
};

#endif
