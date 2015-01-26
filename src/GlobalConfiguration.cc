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
  input_file_names                       = runProcess.getParameter<vector<string>>  ("input");
  input_file_name                        = input_file_names[0];
  gOutputDirectoryName                   = runProcess.getParameter<string>          ("outdir");
  gXSection                              = runProcess.getParameter<double>          ("XSection"); 
  gIsData                                = runProcess.getParameter<bool>            ("isData");
  gVariables::gDebug                     = runProcess.getParameter<bool>            ("debug");
  gmctruthmode                           = runProcess.getParameter<int>             ("mctruthmode");
  for (uint ind = 0; ind < input_file_names.size(); ind++)
    {
      printf("%u %s\n", ind, input_file_names[ind].c_str());
    }
  gnoUncertainties = true;
  
  printf("Configuration succesfully completed\n");
}

void GlobalConfiguration::SetEnvironment_spy()
{
  
}
