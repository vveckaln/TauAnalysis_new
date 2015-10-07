
#include "LIP/TauAnalysis/interface/HierarchicalObjectPool.hh"
#include <vector>
#include <map>
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"

HierarchicalObjectPool::HierarchicalObjectPool()
{
  hierarchy = NULL;
}
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
void HierarchicalObjectPool::GetFromFile(const vector<HistogramDescriptor> * h, TFile *f, const char* c)
{
  printf("virtual gettin from file\n");
}
void HierarchicalObjectPool::ls() const
{
  printf("virtual listing\n");
}
void HierarchicalObjectPool::Write(const char * name, const char * removal)
{
  printf("virtual writing\n");
}
/* void SetFillColor(Color_t);
  void SetMarkerStyle(Style_t);
  void SetDirectoryName(const char *);
  template<class OtherObject>
  void Add(ObjectPool<OtherObject> *);
  template<class OtherObject>
  void Add(ObjectPool<OtherObject> *, const char*);
  void Close();
  void Draw(Option_t * = "");
  virtual ~ ObjectPool();*/
