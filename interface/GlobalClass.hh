#ifndef _GlobalClass_hh
#define _GlobalClass_hh

#include "CERN_RTU/TauAnalysis/interface/GlobalConfiguration.hh"
#include "CERN_RTU/TauAnalysis/interface/GlobalVariables.hh"
using namespace gVariables;

class GlobalClass{
public:
  static GlobalConfiguration* gc_gConfiguration;
  GlobalClass();
  virtual ~GlobalClass(){};
};
#endif
