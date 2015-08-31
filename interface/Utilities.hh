#ifndef _Utilities_hh
#define _Utilities_hh
#include "LIP/TauAnalysis/interface/Register.hh"
#include "TF1.h"
#include "TH1F.h"
using namespace cpregister;
namespace utilities
{
  inline const char * to_char(const bool b){return b ? "true" : "false";};
  TH1D * const GetStatisticsHistogram(const unsigned short sample_ind);
  
  TF1 * HistogramFitGaus(TH1F *&hist, const double interval = 2);
  
}
#endif
