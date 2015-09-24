#include <boost/shared_ptr.hpp>
#include "DataFormats/FWLite/interface/Event.h"

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
#include "TLorentzVector.h"*/
#include "TFile.h"
/*#include "TH1D.h"
#include "TSystem.h"*/
using namespace std;
void TestF(const char * s1 = "", const char * s2 = "pp")
{
  printf("%s %s\n", s1, s2);
};

int main() 
{
  TFile * file = TFile::Open("root://cms-xrd-global.cern.ch//store/mc/Phys14DR/QCD_Pt-80to120_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/10000/606E03E7-C57C-E411-932B-00259073E532.root");
  fwlite::Event event(file);
  unsigned long entry_ind = 0;
  int toReturn = event.size();
  printf("size = %d\n", toReturn);
  for(event.toBegin(); !event.atEnd(); ++event)
    {
      entry_ind++;
      if (entry_ind % 10000 == 0)
	{
	  printf("Read %lu events\n", entry_ind);
	  //getchar();
	}

    }
  file -> Close();

}
