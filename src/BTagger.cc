#include "LIP/TauAnalysis/interface/BTagger.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"

#include "LIP/TauAnalysis/interface/BtagUncertaintyComputer.h"
#include <math.h>
#include "TList.h"

BTagger::BTagger(EventSink<DigestedEvent*> *next_processor_stage):EventProcessor<DigestedEvent*, DigestedEvent*>(next_processor_stage)
{
  activated = false;
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
  events_received = 0;
  events_btag_changed = 0;
}

void BTagger::Run()
{
 
  const double CSV_CUT   = 0.405;
  output_buffer = input_buffer;
  
  for (unsigned long entry_ind = 0; entry_ind < input_buffer -> size(); entry_ind ++)
  {
    events_received ++;
    DigestedEvent *const processed_event = (*input_buffer)[entry_ind];
    for (uint jet_ind = 0; jet_ind < processed_event -> Jets . size(); jet_ind ++)
      {
	Jet * const jet = &processed_event -> Jets . at(jet_ind);
	const double btagvalue = jet -> CSV_discriminator;
	jet -> BTagSFUtil_isBtagged = btagvalue > CSV_CUT;

	if (not activated)
	  {
	    continue;
	  }
	const double jetpt = jet -> Pt();
	const double bseed_sin_phi = sin(jet -> Phi()*1000000);
	const double bseed = abs(static_cast<int>(bseed_sin_phi*100000));
	BTagSFUtil btsfutil( bseed );
	const int bflavid= jet -> genflav;

	TString flavKey("udsg");
	if(abs(bflavid) == 4) flavKey = "c";
	if(abs(bflavid) == 5) flavKey = "b";
	const pair<TString, TString> btagKey("csvL", flavKey);
	if(btagEfficiencyCorrectionGraphs.find(btagKey) != 
	   btagEfficiencyCorrectionGraphs.end())
	  {
	    const TGraphErrors * const mceffGr = 
	      btagEfficiencyCorrectionGraphs[btagKey].first;
	    const TGraphErrors * const sfGr = 
	      btagEfficiencyCorrectionGraphs[btagKey].second;
	    const float eff = mceffGr -> Eval(jetpt);
	    const float sf = sfGr -> Eval(jetpt);
	    bool hasBtagCorr = jet -> BTagSFUtil_isBtagged;
	    btsfutil.modifyBTagsWithSF(hasBtagCorr, sf, eff);
	    if (jet -> BTagSFUtil_isBtagged != hasBtagCorr)
	      {
		printf("jet -> BTagSFUtil_isBtagged != hasBtagCorr\n");
		events_btag_changed ++;
	      }
	    jet -> BTagSFUtil_isBtagged = hasBtagCorr;
	  }
      }
    } 

   if (!output_buffer -> IsEmpty()) ProceedToNextStage();
     
  }

void BTagger::Report()
{
  ContinueReportToNextStage();
  printf("Btagger reports\n");
  printf("Events received %lu\n", events_received);
  printf("Btag modified %lu\n", events_btag_changed);
}

BTagger::~BTagger()
{
  btag_file -> Close();
  delete btag_file;
  btag_file = NULL;
}
