#ifndef _GlobalConfiguration_hh
#define _GlobalConfiguration_hh

#include <vector>
#include <map>

#include "LIP/TauAnalysis/interface/GlobalVariables.hh"

using namespace std;
using namespace gVariables;

class GlobalConfiguration{
public:
  //*********** CONFIGURATION AREA *************
 
  void SetConfiguration(const char *);

  //*********** SPY AREA **********************
  vector<char *> listSpyFiles;
  vector<char *> list_out_Files;
  void SetEnvironment_spy();

};
#endif
