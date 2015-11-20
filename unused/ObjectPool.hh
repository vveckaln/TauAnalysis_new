#ifndef _ObjectPool_hh
#define _ObjectPool_hh
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"
#include "LIP/TauAnalysis/interface/HierarchicalObjectPool.hh"

#include <vector>
#include <map>
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"

class TCanvasPool;
using namespace std;


template<class Object>
class ObjectPool: public HierarchicalObjectPool
{
protected:
  TString title;
  TString directory_name;
public:
  ObjectPool(const char* = "");
  struct iterator
  {
    iterator(typename map<TString, Object*>::iterator it): it(it) {};
    typename map<TString, Object *>::iterator it;
    typename map<TString, Object *>::iterator & Get() {return it;};
    iterator & operator =(const typename map<TString, Object*>::const_iterator & it) 
    {
      this -> it = it; return *this;
    };
    ~iterator() {};
  };

  struct const_iterator
  {
    const_iterator(typename map<TString, Object*>::const_iterator cit): cit(cit) {};
    typename map<TString, Object *>::const_iterator cit;
    typename map<TString, Object *>::iterator & Get() {return cit;};
    iterator & operator =(const typename map<TString, Object*>::const_iterator & cit) 
    {
      this -> cit = cit; return *this;
    };
    ~const_iterator() {};
  };
  typename map<TString, Object *>::iterator it;
  typename map<TString, Object *>::const_iterator cit;
  map<TString, Object*> object_map;
  map<TString, Object*> *operator -> (){return &object_map;};
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
  virtual void GetFromFile(const vector<HistogramDescriptor> * , TFile *, const char* = "");
  virtual void ls() const;
  virtual void Write(const char * name = NULL, const char * removal = 0);
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
