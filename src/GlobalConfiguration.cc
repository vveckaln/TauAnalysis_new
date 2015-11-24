#include "CERN_RTU/TauAnalysis/interface/GlobalVariables.hh"
#include "CERN_RTU/TauAnalysis/interface/GlobalConfiguration.hh"
#include "CERN_RTU/TauAnalysis/interface/Register.hh"

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
     
  if (gVariables::grunmode != "hadd")
    {
      vector<edm::LuminosityBlockRange> luminosityBlockRange =  runProcess.getUntrackedParameter<vector<edm::LuminosityBlockRange> >("lumisToProcess", vector<edm::LuminosityBlockRange>());
    }
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
  gnoUncertainties = true;
  site                                   = runProcess.getParameter<string>          ("site");
  grun                                   = gdtag.Contains("Run2015B") or gdtag.Contains("Asympt_50ns") ? Run2015B : Run2015C;
  printf("Configuration succesfully completed\n");
}

void GlobalConfiguration::SetEnvironment_spy()
{
  
}
