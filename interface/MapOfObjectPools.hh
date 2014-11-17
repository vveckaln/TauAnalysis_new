#ifndef _MapOfObjectPools_hh
#define _MapOfObjectPools_hh
#include "LIP/TauAnalysis/interface/ObjectPool.hh"
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"
#include <vector>
#include <map>
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"

using namespace std;
template<class Object>

class MapOfObjectPools{
public:
  MapOfObjectPools();
  typename map<TString, ObjectPool<Object> *>::iterator it;
  //typename map<TString, ObjectPool<Object> *>::const_iterator cit;
  map<TString, ObjectPool<Object>*> ObjectPool_map;
  //ObjectPool(const vector<HistogramDescriptor> * );
  //Object *&operator[](const TString);
  //Object *& at(const TString);
  unsigned long size() const;
  MapOfObjectPools<ObjectPool<Object>*> *Clone(const char * = "") const;
  ObjectPool<Object> *GetObjectPool(const char * = "") const;

  void Reset() const;
  void SetXaxesTitle(const vector<HistogramDescriptor> *) const;
  void SetAllYaxesTitle(const char*) const;
  void SetYaxesTitle(const vector<HistogramDescriptor> *) const;
  void Sumw2() const;
  void GetFromFile(const vector<HistogramDescriptor> * , TFile *);
  void ls() const;
  void Write();
  void SetFillColor(Color_t) const;
  void SetMarkerStyle(Style_t) const;
  void Add(ObjectPool<Object> *);
  void Close();
  void Draw(Option_t * = "");
  ~ MapOfObjectPools();
};

#include "LIP/TauAnalysis/interface/templates/MapOfObjectPools.tpp"
#endif
