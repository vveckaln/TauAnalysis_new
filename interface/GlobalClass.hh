#ifndef _GlobalClass_hh
#define _GlobalClass_hh

#include "TauAnalysis/interface/GlobalConfiguration.hh"
#include "TauAnalysis/interface/GlobalVariables.hh"
using namespace gVariables;

class GlobalClass{
public:
  static GlobalConfiguration* gc_gConfiguration;
  GlobalClass();
  virtual ~GlobalClass(){};
};
#endif
