#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
#include "LIP/TauAnalysis/interface/CPFilePoolRegister.hh"
namespace cpFileRegister
{
  TString     input_file_name  = "";
  TFile     * input_file       = NULL;
  vector<string> input_file_names; 
  TFilePool * input_file_pool  = NULL;
  TFilePool * output_file_pool = NULL;
  TFile     * data_file        = NULL;
  TString     output_file_name = "";
  TFile     * output_file      = NULL;
  vector<TString> output_file_names;

}
