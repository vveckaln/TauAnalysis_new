#ifndef _ObjectPool_hh
#define _ObjectPool_hh
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"
#include <vector>
#include <map>
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"

class TCanvasPool;
using namespace std;
template<class Object>
class ObjectPool{
protected:
  TString title;
  TString directory_name;
public:
  ObjectPool(const char* = "");
  typename map<TString, Object *>::iterator it;
  typename map<TString, Object *>::const_iterator cit;
  map<TString, Object*> object_map;
  ObjectPool(const vector<HistogramDescriptor> * );
  Object *&operator[](const TString);
  Object *& at(const TString);
  unsigned long size() const;
  ObjectPool<Object> *Clone(const char * = "") const;
  void Reset() const;
  void SetTitle();
  TString GetTitle() const {return title;}
  void SetXaxesTitle(const vector<HistogramDescriptor> *) const;
  void SetAllYaxesTitle(const char*) const;
  void SetYaxesTitle(const vector<HistogramDescriptor> *) const;
  void Sumw2() const;
  void GetFromFile(const vector<HistogramDescriptor> * , TFile *, const char* = "");
  void ls() const;
  void Write();
  void SetFillColor(Color_t);
  void SetMarkerStyle(Style_t);
  void SetDirectoryName(const char *);
  template<class OtherObject>
  void Add(ObjectPool<OtherObject> *);
  template<class OtherObject>
  void Add(ObjectPool<OtherObject> *, const char*);
  void Close();
  void Draw(Option_t * = "");
  virtual ~ ObjectPool();
protected:
};

#include "LIP/TauAnalysis/interface/templates/ObjectPool.cpp"
#endif
