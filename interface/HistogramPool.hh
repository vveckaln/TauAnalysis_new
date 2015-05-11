#ifndef _HistogramPool_hh
#define _HistogramPool_hh

#include "LIP/TauAnalysis/interface/PureEvent.hh"
#include "LIP/TauAnalysis/interface/ObjectPool.hh"
#include "LIP/TauAnalysis/interface/HStructure.hh"

#include <map>
#include "TH1D.h"
#include "TString.h"
#include "TFile.h"
#include "TLegend.h"

using namespace std;

class HistogramPool: public ObjectPool<TH1D> 
{
  static unsigned int instances;
  bool temporary;
  TString directory_title;
public:
  HistogramPool();
  map<TString, TH1D*>* histogram_map;
  HistogramPool(const vector<HistogramDescriptor> * , const char* title = "", const char * is_temporary = "");
  void AddObjects(const vector<HistogramDescriptor> *, const char * = "");

  PureEvent *processed_event;
  virtual ~ HistogramPool();
  void SetTitle(const char * directory_title);
  void Fill_Delta_R_lepton_1st_leading_jet();
  void Fill_Abs_Delta_phi_lepton_MET();
  void Fill_eta_tau();
  void AddEntryToLegend(TLegend *& , const char * = "", Option_t* = "lpf");
  void Normalise(HistogramPool *);
};

#endif
