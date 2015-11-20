#ifndef _MapOfTH1DPools_hh
#define _MapOfTH1DPools_hh
#include "LIP/TauAnalysis/interface/MapOfObjectPools.hh"
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"
#include "LIP/TauAnalysis/interface/TFilePool.hh"
#include <vector>
#include <map>
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"

using namespace std;

class MapOfTH1DPools: public MapOfObjectPools<TH1D>
{
public:
  MapOfTH1DPools();
  void AddObjects(const TFilePool &, const HistogramDescriptor &);
  typename map<TString, ObjectPool<TH1D> *>::iterator it;
  virtual ~ MapOfTH1DPools();
};

#endif
