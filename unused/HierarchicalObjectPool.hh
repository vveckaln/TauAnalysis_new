#ifndef _HierarchicalObjectPool_hh
#define _HierarchicalObjectPool_hh
#include "LIP/TauAnalysis/interface/HStructure.hh"
#include <vector>
#include <map>
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
template<class Object>
class ObjectPool;
class HierarchicalObjectPool
{
protected:
public:
  HStructure *hierarchy;

  HierarchicalObjectPool();
  /*ObjectPool(const vector<HistogramDescriptor> * );
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
  void Sumw2() const;*/
  virtual void GetFromFile(const vector<HistogramDescriptor> * , TFile *, const char* = "");
  virtual void ls() const;
  virtual void Write(const char * name = NULL, const char * removal = 0);
    /*void SetFillColor(Color_t);
  void SetMarkerStyle(Style_t);
  void SetDirectoryName(const char *);
  template<class OtherObject>
  virtual void Add(ObjectPool<OtherObject> *){};
  template<class OtherObject>
  virtual void Add(ObjectPool<OtherObject> *, const char*){};
  void Close();
  void Draw(Option_t * = "");
  virtual ~ ObjectPool();*/
};

#endif
