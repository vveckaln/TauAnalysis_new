#include <boost/shared_ptr.hpp>
/*
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
*/
#include <iostream>
#include <vector>
#include "stdio.h"
/*#include "TCanvas.h"
#include "TApplication.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1D.h"
#include "TSystem.h"*/
using namespace std;
void TestF(const char * s1 = "", const char * s2 = "pp")
{
  printf("%s %s\n", s1, s2);
};

int main() 
{
  TestF("hey", "hey2");
  vector<int> test;
  for (uint ind = 0; ind < 10; ind ++)
    {
      test.push_back(ind);
    }
  vector<int>::iterator it = test.begin();
  while (it != test.end())
    {
      if (*it %2 == 1) 
	test.erase(it);
      else 
	it ++;
    };
  for (uint ind = 0; ind < test.size(); ind ++)
    printf("%u\n", test[ind]);
}
