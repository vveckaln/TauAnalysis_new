#ifndef _CPFileRegister_hh
#define _CPFIleRegister_hh

#include "TString.h"
#include "TFile.h"
#include <vector>
using namespace std;
namespace cpFileRegister{
  //********************* CENTRAL PROCESSOR FILE REGISTER ******
  extern TString     input_file_name;
  extern TFile     * input_file;
  extern vector<string> input_file_names;
  extern TFile     * data_file;
  extern TString     output_file_name;
  extern TFile     * output_file;
}
#endif
