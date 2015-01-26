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
  extern bool           gnoUncertainties;
  extern bool           geChONmuChOFF;
  extern bool           gIsData;
  extern double         gXSection;
  extern bool           gDebug; 
  extern int            gmctruthmode;
  extern vector<int>    gjacknifeCfg; 
  extern TString        gInputFileName; 
  extern TString        gOutputFileName;
  extern TString        gBaseDirectoryName; 
  extern TString        gOutputDirectoryName;
  extern vector<double> dataPileupDistributionDouble;
  extern vector<double> singleLepDataPileupDistributionDouble; 
  extern TString        gspyOutputArea;
  extern TString        gsubArea;

}
#endif
