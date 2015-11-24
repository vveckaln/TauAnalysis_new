#include "CERN_RTU/TauAnalysis/interface/gConfiguration.hh"
#include "CERN_RTU/TauAnalysis/interface/GlobalClass.hh"

GlobalConfiguration * GlobalClass::gc_gConfiguration       = new GlobalConfiguration();
GlobalConfiguration * gConfiguration = GlobalClass::gc_gConfiguration;
