#include <boost/shared_ptr.hpp>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TSystem.h"

int main(int argc, char* argv[])
{

gSystem->Load( "libFWCoreFWLite" );
AutoLibraryLoader::enable();
// configure the process
const edm::ParameterSet &runProcess = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("runProcess");
double xsec = runProcess.getParameter<double>("xsec");
 printf("%f\n", xsec);
}
