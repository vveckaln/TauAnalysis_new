#ifndef _GlobalVariables_hh
#define _GlobalVariables_hh

#include <vector>
#include "TSystem.h"
#include "TFile.h"

#include "TString.h"
using namespace::std;

namespace gVariables
{
  typedef double GeV; 
  //******************** CONFIGURATION VARIABLES **********  
  extern bool           gdebug; 
  extern bool           gIsMC;
  extern double         gXSection;
  extern int            gMCTruthmode; 
  extern vector<int>    gjacknifeCfg; 
  extern TString        gInputFileName; 
  extern TString        gOutputFileName;
  extern TString        gBaseDirectoryName; 
  extern TString        gOutputDirectoryName;
}
#endif
