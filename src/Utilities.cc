#include "LIP/TauAnalysis/interface/Utilities.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"

#include "TF1.h"
#include "TH1F.h"
namespace utilities
{

  TH1D * const GetStatisticsHistogram(const unsigned short sample_ind)
  {
    return (TH1D*)hstruct_worker -> GetHStructure(samples_names[sample_ind], "numb_events_selection_stagesSELECTOR_BASE") -> GetRef(); 
  }

  TF1 * HistogramFitGaus(TH1F *&hist, const double interval)
  {
    hist -> Fit("gaus", "0Q");
    if (hist -> GetFunction("gaus") == 0) return NULL;
    const double mean = hist -> GetFunction("gaus") -> GetParameter(1);
    const double sigma = hist -> GetFunction("gaus") -> GetParameter(2);
    delete hist -> GetFunction("gaus");
    hist -> Fit("gaus", "0Q", "", mean - interval * sigma, mean + interval * sigma);
    if (hist -> GetFunction("gaus") == 0) return NULL;
    const Int_t kNotDraw = 1<<9;
    hist -> GetFunction("gaus") -> ResetBit(kNotDraw);
    return hist -> GetFunction("gaus");
    
  }
 
}

