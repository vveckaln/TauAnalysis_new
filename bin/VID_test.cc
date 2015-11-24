#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TFile.h"

int main(int argc, char* argv[])
{
  const char* input_file_name = "root://cms-xrd-global.cern.ch//store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/00C4781D-6B08-E511-8A0A-0025905A6084.root";
  TFile* file = TFile::Open(input_file_name );
  fwlite::Event event(file);
  for(event.toBegin(); !event.atEnd(); ++event)
    {

      pat::ElectronCollection     electrons;

      fwlite::Handle< pat::ElectronCollection > electronsHandle;
      electronsHandle.getByLabel(event, "slimmedElectrons");
      if(electronsHandle.isValid()){ electrons = *electronsHandle;}

      for (pat::ElectronCollection::iterator it = electrons.begin(); it != electrons.end(); it ++)
	{
	  //make ID decision for each elecron
	}
      
    }
}
