#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "EgammaWork/ElectronNtupler/plugins/ElectronNtuplerVIDDemo.cc"

#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"
#include "RecoEgamma/ElectronIdentification/interface/VersionedGsfElectronSelector.h"
#include "TFile.h"
#include "TSystem.h"
int main(int argc, char* argv[])
{
  gSystem->Load( "libFWCoreFWLite.so" );
  gSystem->Load( "libCERN_RTUTauAnalysis.so" );
  AutoLibraryLoader::enable();

  if( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ){
    std::cout << " ERROR: ParametersSet 'process' is missing in your configuration file" << std::endl; exit(0);
  }
  // get the python configuration
  const edm::ParameterSet& process = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  /*fwlite::InputSource inputHandler_(process); fwlite::OutputFiles outputHandler_(process);
  
  // now get each parameter
  const edm::ParameterSet& ana = process.getParameter<edm::ParameterSet>("electronAnalyzer");
  edm::InputTag electrons_( ana.getParameter<edm::InputTag>("electrons") );
  */
  // setup an ID for use
  const edm::ParameterSet& my_ids = process.getParameterSet("my_vid_configuration");
  const edm::ParameterSet& loose_id_conf = my_ids.getParameterSet("loose");
  const edm::ParameterSet& medium_id_conf = my_ids.getParameterSet("medium");
  const edm::ParameterSet& tight_id_conf = my_ids.getParameterSet("tight");
    
  VersionedGsfElectronSelector loose_id(loose_id_conf);
  VersionedGsfElectronSelector medium_id(medium_id_conf);
  VersionedGsfElectronSelector tight_id(tight_id_conf); 


  const char* input_file_name = "root://cms-xrd-global.cern.ch//store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/00C4781D-6B08-E511-8A0A-0025905A6084.root";
  TFile* file = TFile::Open(input_file_name );
  fwlite::Event event(file);
  unsigned long event_number = 0;
  for(event.toBegin(); !event.atEnd(); ++event)
    {

      // ID decisions objects
      pat::ElectronCollection electrons;
      fwlite::Handle< pat::ElectronCollection > electronsHandle;
      electronsHandle.getByLabel(event, "slimmedElectrons");
      if(electronsHandle.isValid()){ electrons = *electronsHandle;}
      unsigned int ind = 0;
      for (pat::ElectronCollection::iterator it = electrons.begin(); it != electrons.end(); it ++)
	{
	  //make ID decision for each elecron
	  if( loose_id(*it, event) ) {
	    std::cout << "Electron at " << ind << " passed loose ID!" << std::endl;
          }
          if( medium_id(*it, event) ) {
	    std::cout << "Electron at " << ind << " passed medium ID!" << std::endl;
          }
          if( tight_id(*it,event) ) {
	    std::cout << "Electron at " << ind << " passed tight ID!" << std::endl;
          }
	  ind ++;
	}
      printf("read %lu\n", event_number);
      //      getchar();
      event_number ++;
      
    }
}
