#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/GlobalConfiguration.hh"
#include "LIP/TauAnalysis/interface/Register.hh"

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TSystem.h"

using namespace gVariables;
using namespace cpregister;
void GlobalConfiguration::SetConfiguration(const char* configuration_file)
{
  
  gSystem->Load( "libFWCoreFWLite.so" );
  gSystem->Load( "libLIPTauAnalysis.so" );
  AutoLibraryLoader::enable();
  const edm::ParameterSet &runProcess = edm::readPSetsFrom(configuration_file) 
-> getParameter<edm::ParameterSet>("PhysicsAnalysisParSet");
  input_file_names                       = runProcess.getUntrackedParameter<vector<std::string> >("input");
  vector<edm::LuminosityBlockRange> luminosityBlockRange =  runProcess.getUntrackedParameter<vector<edm::LuminosityBlockRange> >("lumisToProcess", vector<edm::LuminosityBlockRange>());
  input_file_name                        = input_file_names[0];
  gOutputDirectoryName                   = runProcess.getParameter<string>          ("outdir");
  gXSection                              = runProcess.getParameter<double>          ("XSection"); 
  gIsData                                = runProcess.getParameter<bool>            ("isData");
  gVariables::gDebug                     = runProcess.getParameter<bool>            ("debug");
  gmctruthmode                           = runProcess.getParameter<int>             ("mctruthmode");
  gfile_split                            = runProcess.getParameter<int>             ("file_split");
  gsegment                               = runProcess.getParameter<int>             ("segment");
  gwork_directory                        = runProcess.getParameter<string>          ("work_directory");
  gdset                                  = runProcess.getParameter<string>          ("dset");
  gdtag                                  = runProcess.getParameter<string>          ("dtag");
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
