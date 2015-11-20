#ifndef _CombinedTHStackTH1D_hh
#define _CombinedTHStackTH1D_hh

#include "THStack.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TNamed.h"

using namespace std;

class CombinedTHStackTH1D: public TNamed
{
public:
  CombinedTHStackTH1D();
  THStack * thstack {NULL};
  TH1D * th1d {NULL};
  TGraph * graph {NULL};
  TCanvas * canvas {NULL};
  TLegend * legend {NULL};
  TGraph * CreateRatioGraph();
  TCanvas * ProduceDrawing();
  TLegend * UpdateLegend();
  virtual Int_t	Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
  ~ CombinedTHStackTH1D();
};
#endif
