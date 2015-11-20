#ifndef _CombinedTStackTH1DPool_hh
#define _CombinedTStackTH1DPool_hh

#include "LIP/TauAnalysis/interface/ObjectPool.hh"
#include "LIP/TauAnalysis/interface/CombinedTHStackTH1D.hh"

using namespace std;

class CombinedTHStackTH1DPool: public ObjectPool<CombinedTHStackTH1D>
{
public:
  CombinedTHStackTH1DPool();
  CombinedTHStackPool(const vector<HistogramDescriptor> * );
  void AddObjects(const vector<HistogramDescriptor> * );
  void Process();
  virtual ~ CombinedTHStackTH1DPool();
};
#endif
