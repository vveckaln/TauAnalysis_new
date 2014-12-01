#include <boost/shared_ptr.hpp>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "LIP/TauAnalysis/interface/gConfiguration.hh"

#include <iostream>
#include <vector>
#include "TCanvas.h"
#include "TApplication.h"
#include "TLorentzVector.h"
using namespace std;
class test:public TLorentzVector
{
public:
  test(TLorentzVector lv) : TLorentzVector(lv) {};
};

int main() {
  TApplication myapp("app", 0,0);
  TLorentzVector jet(5,4, 3,100);
  test a(jet);
  TLorentzVector diff(1, 1, 2, 20);
  jet = jet -diff;
  a -= diff;
  printf("%f %f\n", a.Px(), a.Py());
  myapp.Run(kTRUE);
  myapp.Terminate();
}
