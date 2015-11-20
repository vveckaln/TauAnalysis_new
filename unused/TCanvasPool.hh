#ifndef _TCanvasPool_hh
#define _TCanvasPool_hh

#include "LIP/TauAnalysis/interface/ObjectPool.hh"
#include <map>
#include "TCanvas.h"
#include "TString.h"
#include "TFile.h"
//#include "LIP/TopTaus/include/Register.hh"
//using namespace cpregister;
using namespace std;

class TCanvasPool: public ObjectPool<TCanvas>{
public:
  unsigned char cd_pad;
  TCanvasPool();
  map<TString, TCanvas*>* TCanvas_map;
  TCanvasPool(const vector<HistogramDescriptor> * );
  void AddObjects(const vector<HistogramDescriptor> *);
  virtual ~ TCanvasPool();
  void Update();
  void DrawOnAllCanvases(TObject*, Option_t * = "");
  void Save(const char *);
  void SetLogy();
  void cd(const int = 0);
  void Divide(const int, const int) const;
  void SetPad(const int, const char* name, const char* title, Double_t xlow, Double_t ylow, Double_t xup, Double_t yup) const;

};
#endif
