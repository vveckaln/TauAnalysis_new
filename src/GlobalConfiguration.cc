#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/GlobalConfiguration.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TSystem.h"

using namespace gVariables;
using namespace cpFileRegister;
void GlobalConfiguration::SetConfiguration(const char* configuration_file)
{
  
  gSystem->Load( "libFWCoreFWLite.so" );
  gSystem->Load( "libLIPTauAnalysis.so" );
  AutoLibraryLoader::enable();
  const edm::ParameterSet &runProcess = edm::readPSetsFrom(configuration_file) 
-> getParameter<edm::ParameterSet>("PhysicsAnalysisParSet");
  input_file_name          = runProcess.getParameter<string>                  ("input_file_name");
  input_file_names.push_back(input_file_name.Data());
  gnoUncertainties         = runProcess.getParameter<bool>                    ("noUncertainties");
  /*gdebug                   = runProcess.getParameter<bool>                  ("Debug");
  gIsMC                    = runProcess.getParameter<bool>                  ("IsMC");
  gXSection                = runProcess.getParameter<double>                ("XSection");
  gMCTruthmode             = runProcess.getParameter<int>                   ("MCTruthmode");
 
  vector<string> FileNames = runProcess.getParameter<vector<string> >("FileNames");
  gInputFileName           = TString(FileNames[0]);
  gBaseDirectoryName       = runProcess.getParameter<string>                ("BaseDirectoryName");
  TString gOutputFileNames(gSystem -> BaseName(gInputFileName));
  gOutputFileName.ReplaceAll(".root", "");
  if(gMCTruthmode != 0)
    {
      gOutputFileName += "_filt"; 
      gOutputFileName += gMCTruthmode; 
    }
  gOutputDirectoryName     = runProcess.getParameter<string>                 ("OutputDirectoryName");
  gSystem -> Exec("mkdir -p " + gOutputDirectoryName);*/
  printf("Configuration succesfully completed\n");
}

void GlobalConfiguration::SetEnvironment_spy()
{
  
}
