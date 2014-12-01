//#include <boost/shared_ptr.hpp>

#include "LIP/TauAnalysis/interface/gConfiguration.hh"
#include "LIP/TauAnalysis/interface/CentralProcessor.hh"
#include "TSystem.h"

using namespace std;
int main(int argc, char* argv[])
{
  gConfiguration -> SetConfiguration(argv[1]);
  /*CentralProcessor * central_processor = new CentralProcessor();
  central_processor -> LoadSelectorHistDescriptors("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_11/src/LIP/TopTaus/histogram_specifiers/spec_selector_histograms.xml");
  central_processor -> Process("");
  central_processor -> StartTApplication();
  central_processor -> TerminateTApplication();*/
  /*gSystem->Load( "libFWCoreFWLite.so" );
  gSystem->Load( "libLIPTauAnalysis.so" );
  AutoLibraryLoader::enable();
  vector<string> urls;
  urls.push_back("/lustre/ncg.ingrid.pt/cmst3/store/user/cbeiraod/14_08_06_2l2nu_EDMtuples_merged/MC8TeV_TTJetsFullLeptMGDecays_0.root");
  TString url = "/lustre/ncg.ingrid.pt/cmst3/store/user/cbeiraod/14_08_06_2l2nu_EDMtuples_merged/MC8TeV_TTJetsFullLeptMGDecays_0.root"; 
  TFile *file = new TFile(url, "READ");
  printf("file opened\n");
  getchar();
  file -> Close();
  
  // file -> MakeProject("demo", "*", "recreate");
  fwlite::ChainEvent ev(urls);
  printf("created fwlite::ChainEvent\n");
  const Int_t totalEntries= ev.size();
  printf("end %u\n", totalEntries);
  for( int iev=0; iev<totalEntries; iev++ )
    {

      ev.to(iev);

      fwlite::Handle< llvvGenEvent > genEventHandle;
      genEventHandle.getByLabel(ev, "llvvObjectProducersUsed");

      fwlite::Handle< llvvTauCollection > tauCollHandle;
      tauCollHandle.getByLabel(ev, "llvvObjectProducersUsed");
      if(!tauCollHandle.isValid()){printf("llvvLeptonCollection Object NotFound\n");continue;}
      llvvTauCollection taus = *tauCollHandle;   
      for(size_t itau=0; itau<taus.size(); itau++)
	{
	  llvvTau& tau = taus[itau];
	  printf("%f\n", tau.Pt());
	} 
      getchar();
    }
  */
  //delete central_processor;
}
