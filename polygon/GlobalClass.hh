#ifndef _GlobalClass_hh
#define _GlobalClass_hh

#include "LIP/TauAnalysis/interface/GlobalConfiguration.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
using namespace gVariables;

class GlobalClass{
public:
  static GlobalConfiguration* gc_gConfiguration;
  GlobalClass();
  virtual ~GlobalClass(){};
};
#endif
