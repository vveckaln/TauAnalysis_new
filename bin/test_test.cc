#include <boost/shared_ptr.hpp>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

#include "LIP/TauAnalysis/interface/Table.h"
#include "LIP/TauAnalysis/interface/rootdouble.h"
#include "LIP/TauAnalysis/interface/Parser.hh"
#include "LIP/TauAnalysis/interface/HStructure.hh"
#include "LIP/TauAnalysis/interface/HStructure_TFile.hh"
#include "LIP/TauAnalysis/interface/HStructure_TH1D.hh"

#include <iostream>
#include <vector>
#include "TCanvas.h"
#include "TApplication.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1D.h"
#include "TSystem.h"
using namespace std;
void TestF(const char * s1 = "", const char * s2 = "pp")
{
  printf("%s %s\n", s1, s2);
};

int main() 
{
  TestF("hey", "hey2");
  /* Parser *parser = new Parser;
  HStructure * structure = parser -> CreateHierarchicalStructure("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/histogram_specifiers/spec_samples_test.xml");
  delete parser;
  printf("LISTING FORWARD THIS\n");
  structure -> test();
  getchar();

  printf(" LISTING FORWARD ALL\n");
  structure -> test("allsample");
  getchar();

  printf("LISTING FORWARD DESCENDANTS\n");
  structure -> test("descendantssample");
  getchar();

  printf("LISTING FORWARD CHILDREN\n");
  structure -> test("childrensample");
  getchar();
  
  printf("LISTING BACKWARD\n");
  structure -> ls_bckw();
  getchar();

  printf("LISTING BACKWARD ALL\n");
  structure -> ls_bckw("all sample");
  getchar();

  printf(" LISTING BACKWARD DESCENDANTS\n");
  structure -> ls_bckw("descendants sample");
  getchar();
  
  printf("LISTING BACKWARD CHILDREN\n");
  structure -> ls_bckw("children sample");
  getchar();*/
  
  
}
