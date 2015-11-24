#define _CPFIleRegister_hh

#include "TString.h"
#include "TFile.h"
#include "TauAnalysis/interface/TFilePool.hh"
#include <vector>
using namespace std;
{
  //********************* CENTRAL PROCESSOR FILE REGISTER ******
  extern TString     input_file_name;
  extern TFile     * input_file;
  extern vector<string> input_file_names;
  extern TFile     * data_file;
  extern TString     output_file_name;
  extern TFile     * output_file;
  extern vector<TString> output_file_names;
}
#endif
