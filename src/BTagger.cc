#include "LIP/TauAnalysis/interface/BTagger.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"

#include "LIP/TauAnalysis/interface/BtagUncertaintyComputer.h"
#include <math.h>
#include "TList.h"
#include "TMath.h"
using namespace gVariables;
BTagger::BTagger(EventSink<event_type> *next_processor_stage):EventProcessor<event_type, event_type>(next_processor_stage)
{
  activated           = true;
  events_received     = 0;
  events_btag_lowered = 0;
  events_btag_raised  = 0;
  btag_file           = NULL;
  if (gIsData) return;
  btag_file = new TFile("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/weights/btagEff.root", "READ");

  const TList *dirs = btag_file -> GetListOfKeys();
  for(int itagger = 0; itagger < dirs -> GetEntries(); itagger++)
    {
      const TString iDir(dirs -> At(itagger) -> GetName());
      btagEfficiencyCorrectionGraphs[ pair<TString, TString>(iDir,"b") ]
= pair<TGraphErrors *, TGraphErrors *>
	( (TGraphErrors *) btag_file -> Get(iDir + "/beff"), 
	  (TGraphErrors *) btag_file -> Get(iDir + "/sfb") );
      btagEfficiencyCorrectionGraphs[ pair<TString, TString>(iDir, "c") ]
= pair<TGraphErrors *,TGraphErrors *>
	((TGraphErrors *) btag_file -> Get(iDir + "/ceff"), 
	 (TGraphErrors *) btag_file -> Get(iDir + "/sfc"));
      btagEfficiencyCorrectionGraphs[ pair<TString, TString>(iDir, "udsg") ]
= pair<TGraphErrors *, TGraphErrors *>
	( (TGraphErrors *) btag_file -> Get(iDir + "/udsgeff"), 
	  (TGraphErrors *) btag_file -> Get(iDir + "/sfudsg") );
    }
  

}

void BTagger::Run()
{
 
  //const float CSV_CUT   = /*0.405*/ 0.679;
  output_buffer = input_buffer;
  bool print_mode;
  for (EventBuffer<event_type>::iterator it = input_buffer -> begin(); it != input_buffer -> end(); it ++)
    {
      print_mode = false;
      unsigned int nbtags(0);
      events_received ++;
      //if (processed_event -> Event == 27736402) 
      if (print_mode) printf("EVENT IDENTITY %u %u %u\n", it -> Run, it -> Lumi, it -> Event);
      
      for (uint jet_ind = 0; jet_ind < it -> jets . size(); jet_ind ++)
	{
	  pat::Jet * const jet             = &it -> jets . at(jet_ind);
	  
	  if (print_mode)
	    {
	      
	    }

	  if (gIsData)
	    {
	      continue;
	    }


	  const double jetpt = jet -> pt();
	  const double bseed_sin_phi = TMath::Sin(jet -> phi()*1000000);
	  const double bseed = abs(static_cast<int>(bseed_sin_phi*100000));
	  BTagSFUtil btsfutil( bseed );
	   const int bflavId = jet -> partonFlavour();
	  TString flavKey("udsg");
	  if(abs(bflavId) == 4) flavKey = "c";
	  if(abs(bflavId) == 5) flavKey = "b";
	  const pair<TString, TString> btagKey("csvL", flavKey);
	  if(btagEfficiencyCorrectionGraphs.find(btagKey) != 
	     btagEfficiencyCorrectionGraphs.end())
	    {
	      const TGraphErrors * const mceffGr = 
		btagEfficiencyCorrectionGraphs[btagKey].first;
	      const TGraphErrors * const sfGr = 
		btagEfficiencyCorrectionGraphs[btagKey].second;
	      const float eff = mceffGr -> Eval(jetpt);
	      const float sf  = sfGr    -> Eval(jetpt);
	      float const leff(0.13), sfl(1.05);
	      const float bDiscriminator = jet -> bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
	      bool hasCSVtag(bDiscriminator > 0.423);
	      const bool hasCSVtag_old = hasCSVtag;
              if(abs(bflavId) == 5) 
		btsfutil.modifyBTagsWithSF(hasCSVtag, sf,   eff);
              else if(abs(bflavId) == 4) 
		btsfutil.modifyBTagsWithSF(hasCSVtag, sf/5, eff);
              else	
		btsfutil.modifyBTagsWithSF(hasCSVtag, sfl,  leff);
	      if (hasCSVtag) 
		nbtags ++;
	      if (hasCSVtag_old > hasCSVtag)
		{
		  events_btag_lowered ++;
		}
	      if (hasCSVtag_old < hasCSVtag)
		{
		  events_btag_raised ++;
		}

	    }
	  if (print_mode) getchar();
	  
	}
      if (nbtags < 1)
	input_buffer -> erase(it);
    } 

  if (!output_buffer -> IsEmpty()) ProceedToNextStage();
}

void BTagger::Report()
{
  printf("Btagger reports\n");
  printf("Events received %lu\n", events_received);
  printf("Btag raised %lu\n",     events_btag_raised);
  printf("Btag lowered %lu\n",    events_btag_lowered);
  printf("Btag changed %lu\n",    events_btag_lowered + events_btag_raised);
  ContinueReportToNextStage();

}

BTagger::~BTagger()
{
  if (btag_file)
    {
      btag_file -> Close();
      delete btag_file;
      btag_file = NULL;
    }
}
