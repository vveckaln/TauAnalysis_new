#ifndef _THStackPool_hh
#define _THStackPool_hh

#include "LIP/TauAnalysis/interface/ObjectPool.hh"
#include "LIP/TauAnalysis/interface/HStructure.hh"

#include <map>
#include "THStack.h"
#include "TString.h"
#include "TFile.h"
#include "TLegend.h"

using namespace std;

class THStackPool: public ObjectPool<THStack>
{
public:
  TLegend * legend;
  THStackPool();
  THStackPool(const vector<HistogramDescriptor> * );
  void AddObjects(const vector<HistogramDescriptor> * , const char * = "");
  TLegend* DrawLegend();
  virtual ~ THStackPool();
};
#endif
