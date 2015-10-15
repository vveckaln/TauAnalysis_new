#include "LIP/TauAnalysis/interface/GlobalVariables.hh"

namespace gVariables
{
  bool           gnoUncertainties;
  bool           geChONmuChOFF;
  bool           gIsData;
  double         gXSection;
  bool           gDebug; 
  unsigned char  gmctruthmode;
  unsigned char  gfile_split;
  unsigned char  gsegment;
  vector<int>    gjacknifeCfg; 
  TString        grunmode;
  TString        gInputFileName; 
  TString        gOutputFileName;
  TString        gBaseDirectoryName; 
  TString        gOutputDirectoryName;
  TString        gspyOutputArea;
  TString        gsubArea;
  TString        gwork_directory;
  TString        gdset;
  TString        gdtag;
  TString        site;
  vector<double> dataPileupDistributionDouble; 
  vector<double> singleLepDataPileupDistributionDouble; 
  vector<edm::LuminosityBlockRange> luminosityBlockRange;
} 
