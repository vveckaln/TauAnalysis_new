#ifndef _GlobalVariables_hh
#define _GlobalVariables_hh
#include "DataFormats/Provenance/interface/LuminosityBlockRange.h"

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
  extern unsigned char  gmctruthmode;
  extern unsigned char  gfile_split;
  extern unsigned char  gsegment;
  extern vector<int>    gjacknifeCfg; 
  extern TString        gInputFileName; 
  extern TString        gOutputFileName;
  extern TString        gBaseDirectoryName; 
  extern TString        gOutputDirectoryName;
  extern vector<double> dataPileupDistributionDouble;
  extern vector<double> singleLepDataPileupDistributionDouble; 
  extern TString        gspyOutputArea;
  extern TString        gsubArea;
  extern TString        gwork_directory;
  extern TString        gdset;
  extern TString        gdtag;
  extern vector<edm::LuminosityBlockRange> luminosityBlockRange;
}
#endif
