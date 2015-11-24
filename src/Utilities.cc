#include "CERN_RTU/TauAnalysis/interface/Utilities.hh"
#include "CERN_RTU/TauAnalysis/interface/HStructure_worker.hh"

#include "TF1.h"
#include "TH1F.h"
namespace utilities
{

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

