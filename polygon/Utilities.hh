#ifndef _Utilities_hh
#define _Utilities_hh
#include "TF1.h"
#include "TH1F.h"
namespace utilities
{
  inline const char * to_char(const bool b){return b ? "true" : "false";};
  TF1 * HistogramFitGaus(TH1F *&hist, const double interval = 2);
  
}
#endif
