#ifndef _THStackPool_hh
#define _THStackPool_hh

#include "LIP/TauAnalysis/interface/ObjectPool.hh"
#include <map>
#include "THStack.h"
#include "TString.h"
#include "TFile.h"

using namespace std;

class THStackPool: public ObjectPool<THStack>{
public:
  THStackPool();
  map<TString, THStack*>* THStack_map;
  THStackPool(const vector<HistogramDescriptor> * );
  void AddObjects(const vector<HistogramDescriptor> * );

  virtual ~ THStackPool();
};
#endif
