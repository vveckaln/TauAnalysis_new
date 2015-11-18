#ifndef _Utilities_hh
#define _Utilities_hh
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"

#include "TF1.h"
#include "TH1F.h"
using namespace cpregister;
namespace utilities
{
  inline const char * to_char(const bool b){return b ? "true" : "false";};
  inline TH1D * const GetStatisticsHistogram(const unsigned short sample_ind)
  {
    return (TH1D*)hstruct_worker -> GetHStructure(samples_names[sample_ind], "numb_events_selection_stagesSELECTOR_BASE") -> GetRef(); 
  };
  inline TH1D * const GetSelectorHistogram()
  {
    return (TH1D*)hstruct_worker -> GetHStructure("generic_name", "numb_events_selection_stagesCHANNELGATE") -> GetRef(); 
  };

  TF1 * HistogramFitGaus(TH1F *&hist, const double interval = 2);
  
}
#endif
