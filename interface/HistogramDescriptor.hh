#ifndef _HistogramDescriptor_hh
#define _HistogramDescriptor_hh
#include "TString.h"
struct HistogramDescriptor
{
  TString histogram_title;
  TString Xaxis_title;
  TString Yaxis_title;
  int     nbinsx;
  double  xlow;
  double  xup;
};
#endif
