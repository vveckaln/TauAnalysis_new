#include "LIP/TauAnalysis/interface/GlobalVariables.hh"

namespace gVariables
{
  bool           gnoUncertainties;
  bool           geChONmuChOFF;
  bool           gdebug; 
  bool           gIsData;
  double         gXSection;
  int            gMCTruthmode; 
  vector<int>    gjacknifeCfg; 
  TString        gInputFileName; 
  TString        gOutputFileName;
  TString        gBaseDirectoryName; 
  TString        gOutputDirectoryName;
  vector<double> dataPileupDistributionDouble; 
  vector<double> singleLepDataPileupDistributionDouble; 
  double         XSection;
} 
