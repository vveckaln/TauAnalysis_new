#ifndef _HistogramPlotter_hh
#define _HistogramPlotter_hh

#include "TFile.h"
#include "TString.h"
#include <vector>
using namespace std;
class HistogramPlotter
{
public:
  HistogramPlotter();
  void SumData() const;
  void AddHistograms() const;
  void StackHistograms(const char *);
  ~HistogramPlotter();
protected:
  
};
#endif
