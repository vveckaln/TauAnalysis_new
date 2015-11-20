#ifndef _TFilePool_hh
#define _TFilePool_hh

#include "LIP/TauAnalysis/interface/ObjectPool.hh"
#include <map>
#include "TCanvas.h"
#include "TString.h"
#include "TFile.h"
#include <vector>
using namespace std;

class TFilePool: public ObjectPool<TFile>
{
public:
  TFilePool();
  TFilePool(const vector<string> &, const Option_t * = "READ");
  TFilePool(const vector<TString> &, const Option_t * = "READ");

  map<TString, TFile*>& TFile_map = object_map;
  void AddObjects(const char *);
  void Close();
  virtual ~ TFilePool();
};
#endif
