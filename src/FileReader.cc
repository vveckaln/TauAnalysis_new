#include "LIP/TauAnalysis/interface/FileReader.hh"
#include "LIP/TauAnalysis/interface/EventBuffer.hh"

#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/FWLite/interface/Handle.h"

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/PatUtils.h"

#include <iostream>
using namespace cpregister;
using namespace gVariables;

FileReader::FileReader(EventSink<event_type> * next_processor_stage):
EventProcessor<event_type, event_type>(next_processor_stage)
{
  goodLumiFilter  = new lumiUtils::GoodLumiFilter(luminosityBlockRange);
  read = 0;
  muon_trigger = 0;
  goodLumiFilter_continue = 0;
}

void FileReader::Run()
{
  fprintf(stderr, "Starting FileReader::Run\n");
  unsigned long entry_ind = 0;

  for(unsigned int f = 0; f < input_file_names.size(); f++)
    {
      printf ("FileReader: Opening file %s\n", input_file_names[f].c_str());

      TFile* file = TFile::Open(input_file_names[f].c_str() );
      printf ("FileReader: Reading file %s\n", input_file_names[f].c_str());
      //getchar();
      fwlite::Event event(file);
      for(event.toBegin(); !event.atEnd(); ++event)
	{
	  entry_ind++;
	  ReadEvent_llvv Event; 
	  event_type read_event= &Event; //output_buffer -> GetWriteSlot(); 
	  output_event = read_event;
	  if (entry_ind % 10000 == 0)
	    {
	      printf("Read %lu events\n", entry_ind);
	      //getchar();
	    }

	  //Skip bad lumi
	  if(!goodLumiFilter -> isGoodLumi(event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock()))
	    {
	      goodLumiFilter_continue ++;
	      continue;	      
	    }
	  read_event -> Run         = event.eventAuxiliary().run();
	  read_event -> Lumi        = event.eventAuxiliary().luminosityBlock();
	  read_event -> Event       = event.eventAuxiliary().event();
	  edm::TriggerResultsByName tr = event.triggerResultsByName("HLT");
	  
	  /*	  read_event -> eTrigger    =
                          gIsData ? 
			  utils::passTriggerPatterns (tr, "HLT_Ele23_WPLoose_Gsf_v*") :
                          utils::passTriggerPatterns (tr, "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v*");
	  read_event -> muTrigger  =
                          gIsData ? 
	                  utils::passTriggerPatterns (tr, "HLT_IsoMu18_v*") :
                          utils::passTriggerPatterns (tr, "HLT_IsoMu17_eta2p1_v*");*/
	  read_event ->  eTrigger = 
                          gIsData ? 
	                  utils::passTriggerPatterns (tr, "HLT_Ele27_WPLoose_Gsf_v*", "HLT_Ele27_eta2p1_WPLoose_Gsf_v1" )  
	                  :
	                  utils::passTriggerPatterns (tr, "HLT_Ele27_eta2p1_WP75_Gsf_v*");
                          
	  read_event -> muTrigger = utils::passTriggerPatterns (tr, "HLT_IsoMu20_eta2p1_v*");
	  read_event -> eeTrigger          = utils::passTriggerPatterns(tr, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*");
	  read_event -> muTrigger          = utils::passTriggerPatterns(tr, "HLT_Mu34_TrkIsoVVL_v*");
	  if (read_event -> muTrigger)
	    muon_trigger ++;
	  //printf("muTrigger %s\n", read_event -> muTrigger ? "true" : "false");*/
	  read_event -> mumuTrigger        = utils::passTriggerPatterns(tr, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*", "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*"); 
	  read_event -> emuTrigger         = utils::passTriggerPatterns(tr, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*");
	  if(!goodLumiFilter -> isGoodLumi(read_event -> Run, read_event -> Lumi))
	    continue;
	  fwlite::Handle< reco::VertexCollection > vtxHandle;
	  vtxHandle.getByLabel(event, "offlineSlimmedPrimaryVertices");
	  if (vtxHandle.isValid())read_event -> vertices = *vtxHandle;

	  fwlite::Handle< reco::GenParticleCollection > genHandle;
	  genHandle.getByLabel(event, "prunedGenParticles");
	  if (genHandle.isValid()) read_event -> gen = *genHandle;

	  fwlite::Handle< pat::MuonCollection > muonsHandle;
	  muonsHandle.getByLabel(event, "slimmedMuons");
	  if(muonsHandle.isValid()){ read_event -> muons = *muonsHandle;}

	  fwlite::Handle< pat::ElectronCollection > electronsHandle;
	  electronsHandle.getByLabel(event, "slimmedElectrons");
	  if(electronsHandle.isValid()){ read_event -> electrons = *electronsHandle;}
      

	  fwlite::Handle< pat::TauCollection > tausHandle;
	  tausHandle.getByLabel(event, "slimmedTaus");
	  if(tausHandle.isValid()){ read_event -> taus = *tausHandle;}

	  fwlite::Handle< pat::JetCollection > jetsHandle;
	  jetsHandle.getByLabel(event, "slimmedJets");
	  if(jetsHandle.isValid()){ read_event -> jets = *jetsHandle;}

	  fwlite::Handle< pat::METCollection > metsHandle;
	  metsHandle.getByLabel(event, "slimmedMETs");
	  if(metsHandle.isValid()){ read_event -> MET = *metsHandle;}

	  fwlite::Handle< double > rhoHandle;
	  rhoHandle.getByLabel(event, "fixedGridRhoFastjetAll");
	  if(rhoHandle.isValid()){ read_event -> rho = *rhoHandle;}
      
	  fwlite::Handle< vector<PileupSummaryInfo> > puInfoH;
	  puInfoH.getByLabel(event, "addPileupInfo");
	  if (puInfoH.isValid()) read_event  -> PU = *puInfoH;

	  fwlite::Handle< GenEventInfoProduct > genEventInfoHandle;
	  genEventInfoHandle.getByLabel(event, "generator");
	  if(genEventInfoHandle.isValid()){ read_event -> genEventInfo = * genEventInfoHandle; }

	  fwlite::Handle< pat::PhotonCollection > photonsHandle;
	  photonsHandle.getByLabel(event, "slimmedPhotons");
	  if(photonsHandle.isValid()){ read_event -> photons = *photonsHandle;}

	  ProceedToNextStage();
   
	  
	  // output_buffer = NULL;
	  //output_buffer = new EventBuffer<event_type>(10, "independent");
	  //}

	} 
      read += entry_ind;
      file -> Close();
      delete file;
    }
  if(gIsData)
    {
      FILE *in;
      char buff[512];
      cerr<<"here"<<endl;
      TString cmd("if [ -d "); cmd += gOutputDirectoryName + "/output/event_analysis/" + gdtag + "/luminosities" + " ]; \nthen\necho \"true\"\nelse\necho \"false\"\nfi";
 // "if [ -d \"/afs/cern.ch/work/v/vveckaln/private/CMSSW_7_4_2/src/LIP/TauAnalysis1\" ]; \nthen\necho \"true\"\nelse\necho \"false\"\nfi"
      if(!(in = popen(cmd, "r")))
	{
	  return ;
	}
      while(fgets(buff, sizeof(buff), in) != NULL)
	{
	  cerr<<"buffer"<<buff<<endl;
	  if (string(buff).compare(string("true\n")) != 0)
	    {
	      TString cmd1("mkdir "); cmd1 += gOutputDirectoryName + "/output/event_analysis/" + gdtag + "/luminosities";
	      system(cmd1);
	    }

	}
      pclose(in);

      goodLumiFilter -> FindLumiInFiles(input_file_names);
      goodLumiFilter -> DumpToJson((gOutputDirectoryName + "/output/event_analysis/" + gdtag + "/luminosities/" + gdtag + "_luminosities_" + TString(to_string(gsegment)) + ".json").Data());
    }
}
 
void FileReader::Report()
{
  printf("Read %lu events\n", read);
  printf("muon trigger %lu goodLumiFilter continued %lu\n", muon_trigger, goodLumiFilter_continue);
  ContinueReportToNextStage();
}


FileReader::~FileReader()
{
  delete goodLumiFilter;
}
