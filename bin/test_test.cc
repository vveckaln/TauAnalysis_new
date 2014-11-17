#include <boost/shared_ptr.hpp>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "LIP/TauAnalysis/interface/gConfiguration.hh"

int main(int argc, char* argv[])
{

  gConfiguration -> SetConfiguration(argv[1]);

 printf("finish\n");
}
