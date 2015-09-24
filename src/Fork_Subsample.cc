#include "LIP/TauAnalysis/interface/Fork_Subsample.hh"#include "LIP/TauAnalysis/interface/GlobalVariables.hh"#include "LIP/TauAnalysis/interface/Parser.hh"#include "LIP/TauAnalysis/interface/Register.hh"#include "LIP/TauAnalysis/interface/HStructure_worker.hh"#include <math.h>#include "TCanvas.h"using namespace cpregister;using namespace gVariables;Fork_Subsample::Fork_Subsample(EventSink<event_type> *next_processor_stage):EventProcessor<event_type, event_type>(next_processor_stage){    if (IsGeneric) SetEnvironment_generic();  if (IsDY) SetEnvironment_DY();  if (IstW) SetEnvironment_TTbarMC();  if (IsTTbarMC) SetEnvironment_TTbarMC();  if (IsWJets) SetEnvironment_WJets();  received = 0;   passed = 0;}void Fork_Subsample::Run(){  received ++;  ngen_electron = 0; ngen_muon = 0; ngen_tau = 0; ngen_quark = 0;  if (IsTTbarMC) CountLeptons_TTbarMC();   if (IsWJets) CountLeptons_WJets();   if (IsDY) CountLeptons_DY();   //   printf("IsDY %s\n", IsDY ? "true" : "false");  for (number_active_sample = 0; number_active_sample < *number_of_samples; number_active_sample ++)    {      ReadEvent_llvv event;      if (number_active_sample < *number_of_samples - 1)	{	  event = *input_event;	  output_event = &event;	}      else	output_event = input_event;            bool sample_valid = (this ->* sample_check_ptr[number_active_sample])();;      if (not sample_valid)	continue;  /*printf("EVENT IDENTITY %u %u %u\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event);    processed_event -> ls("electron", "verbose");    processed_event -> ls("muon", "verbose");    printf("Event passed quality cleaning       %s\n", PassedCleaning ? "true" : "false");    printf("Leading lepton is a muon            %s\n", LeptonCorresponds ? "true" : "false");    printf("Muon trigger fired                  %s\n", Trigger_Fired ? "true" : "false");    printf("Event was selected for muon channel %s\n", channel_opened ? "true" : "false");    printf("---------------- NEXT -----------------------\n");*/            passed ++;      ProceedToNextStage();    }}bool Fork_Subsample::CheckTTbarMC_muon_tau() const{      if(ngen_quark == 0 and ngen_tau == 1      and ngen_muon == 1      and ngen_electron == 0)    return true;  else return false;}bool Fork_Subsample::CheckTTbarMC_lepton_jets() const{  if(ngen_tau == 0     and (ngen_muon + 	  ngen_electron) >= 1)     return true;  else return false;}bool Fork_Subsample::CheckTTbarMC_dilepton_muon_electron() const{  if(ngen_quark == 0 and ngen_tau == 0     and ngen_muon >= 1     and ngen_electron >= 1)     return true;  else return false;}bool Fork_Subsample::CheckTTbarMC_dilepton_muon_muon() const{  if(ngen_quark == 0 and ngen_tau == 0     and ngen_muon >= 2     and ngen_electron == 0)     return true;  else return false;}bool Fork_Subsample::CheckTTbarMC_tau_jets() const{  if(ngen_quark == 0 and ngen_tau == 1     and ngen_muon == 0     and ngen_electron == 0)    return true;  else return false;}bool Fork_Subsample::CheckTTbarMC_tau_tau() const{  if(ngen_quark == 0 and ngen_tau == 2     and ngen_muon == 0     and ngen_electron == 0)     return true;  else return false;}bool Fork_Subsample::CheckTTbarMC_hadronic() const{  if(ngen_quark == 0 and ngen_tau == 0     and ngen_muon == 0     and ngen_electron == 0)     return true;  else return false;}bool Fork_Subsample::CheckDY_lepton_lepton() const{  if(ngen_tau == 0      and ngen_muon + ngen_electron == 2)     return true;  else return false;}bool Fork_Subsample::CheckDY_tau_tau() const{  if(ngen_tau == 2      and ngen_muon == 0      and ngen_electron == 0)     return true;  else return false;}bool Fork_Subsample::CheckWJets() const{    //printf(" quarks %u electrons %u muons %u taus %u\n", ngen_quark, ngen_electron, ngen_muon, ngen_tau);   return true;  if (not geChONmuChOFF)    if (ngen_quark == 0 and ngen_muon == 1) return true;    else return false;  else    if (ngen_quark == 0 and ngen_electron == 1) return true;    else return false;  //  return false;    }void Fork_Subsample::SetEnvironment_TTbarMC() {  typedef bool (Fork_Subsample::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &Fork_Subsample::CheckTTbarMC_muon_tau,       &Fork_Subsample::CheckTTbarMC_lepton_jets,       &Fork_Subsample::CheckTTbarMC_dilepton_muon_electron,       &Fork_Subsample::CheckTTbarMC_dilepton_muon_muon,      &Fork_Subsample::CheckTTbarMC_tau_jets,      &Fork_Subsample::CheckTTbarMC_tau_tau,      &Fork_Subsample::CheckTTbarMC_hadronic,     };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }  }void Fork_Subsample::SetEnvironment_DY() {  typedef bool (Fork_Subsample::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &Fork_Subsample::CheckDY_lepton_lepton,       &Fork_Subsample::CheckDY_tau_tau         };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}void Fork_Subsample::SetEnvironment_WJets() {  typedef bool (Fork_Subsample::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &Fork_Subsample::CheckWJets    };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}void Fork_Subsample::SetEnvironment_generic() {  typedef bool (Fork_Subsample::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &Fork_Subsample::CheckGeneric     };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}void Fork_Subsample::CountLeptons_TTbarMC() {    std::vector<const reco::Candidate*> W_Sons;  for(size_t ig = 0; ig < input_event -> gen.size(); ig++)    {       const reco::GenParticle & p = input_event -> gen[ig];      int id_p   = p.pdgId();             //select tops                                                                                                                              if(abs(id_p) != 6) continue;      for(size_t b = 0; b < p.numberOfDaughters(); ++ b)	{          const reco::Candidate * top_daughter = p.daughter(b);          //store W and ch. higgs daughters                                                                                                            if(abs(top_daughter->pdgId()) == 24 || abs(top_daughter->pdgId()) == 37)            {	      for(size_t c = 0; c < top_daughter->numberOfDaughters(); ++c)		{                  const reco::Candidate * W_daughter = top_daughter -> daughter(c);                  if(abs(W_daughter->pdgId()) != 24 && abs(W_daughter->pdgId()) != 37) 		    W_Sons.push_back(W_daughter);                }            }	}    }    for(std::vector<const reco::Candidate*>::const_iterator Wson_i = W_Sons.begin(); Wson_i != W_Sons.end(); Wson_i++)    {      int id_Wson = (*Wson_i) -> pdgId();      //taus must be traced further                                                                                                            if(abs((*Wson_i) -> pdgId()) == 15)	{	  int tempLepton = 0;	  for(size_t c = 0; c < (*Wson_i) -> numberOfDaughters(); ++ c)	    {	      const reco::Candidate * TauSon = (*Wson_i) -> daughter(c);	      if(abs(TauSon->pdgId()) == 15)		{		  for(size_t d = 0; d < TauSon->numberOfDaughters(); ++ d)		    {                      const reco::Candidate * TauSon2 = TauSon -> daughter(d);                      int tausonid = abs(TauSon2 -> pdgId());                      if     (tausonid == 11)			{			  tempLepton = 11; 			}                      else if(tausonid == 13)			{			  tempLepton = 13; 			}		    }		}	      else if(abs(TauSon->pdgId()) == 11 ) 		{		  tempLepton = 11; 		}	      else if(abs(TauSon->pdgId()) == 13 ) 		{		  tempLepton = 13;		}	    }	  if     (tempLepton == 11) 	    { 	      ngen_electron ++;  	    }	  else if(tempLepton == 13) 	    {	      ngen_muon++;	    }	  else                      	    { 	      ngen_tau++;	    }	}      else      {	switch(abs(id_Wson))	  {   	    case 1:  ngen_quark++;  break;	    case 2:  ngen_quark++;  break;	    case 3:  ngen_quark++;  break;	    case 4:  ngen_quark++;  break;	    case 5:  ngen_quark++;  break;	    case 6:  ngen_quark++;  break;	  case 11: ngen_electron++; break;	  case 13: ngen_muon++; break;	  case 15: ngen_tau++; break; 	  }      }    }}    //Code to disentangle W+jets in enu, munu, taunuvoid Fork_Subsample::CountLeptons_WJets(){      for(size_t i = 0; i < input_event -> gen.size(); ++ i)     {		      const reco::GenParticle & p = input_event -> gen[i];	      int id_p   = p.pdgId();      if( abs(id_p) == 24 )	{      //If we find a W	            for(size_t b = 0; b < p.numberOfDaughters(); ++ b)	    {	      const reco::Candidate * Wson_i = p.daughter(b);	    	      int id_Wson = Wson_i->pdgId();	    	      //taus must be traced further	      if(abs(id_Wson) == 15)		{	    	         		  int tempLepton = 0;		  for(size_t c = 0; c < Wson_i->numberOfDaughters(); ++ c)		    {		      const reco::Candidate * TauSon = Wson_i->daughter(c);		      if(abs(TauSon->pdgId()) == 15){			//cout<<"Tau daughetrs "<<TauSon->numberOfDaughters()<<endl;			for(size_t d = 0; d < TauSon->numberOfDaughters(); ++ d)			  {			    const reco::Candidate * TauSon2 = TauSon->daughter(d);			    int tausonid = abs(TauSon2->pdgId());			    //cout<<"tau daughter Id "<<tausonid<<" status "<<TauSon2->status()<<endl;			    if     (tausonid == 11){tempLepton = 11;}			    else if(tausonid == 13){tempLepton = 13;}			    //else if(tausonid == 12 || tausonid==14 || tausonid==16) neutrinos.push_back(TauSon2);			  }		      }		      else if(abs(TauSon->pdgId()) ==11 ) {tempLepton = 11;}		      else if(abs(TauSon->pdgId()) ==13 ) {tempLepton = 13;}		      //else if(abs(TauSon->pdgId())==12 || abs(TauSon->pdgId())==14 || abs(TauSon->pdgId())==16) neutrinos.push_back(TauSon);		    }  		  if     (tempLepton == 11) { ngen_electron ++;  }		  else if(tempLepton == 13) { ngen_muon++;      }		  else                      { ngen_tau++;       }	    		}	      else{	  		switch(abs(id_Wson))		  {		  case 1:  ngen_quark++;  break;		  case 2:  ngen_quark++;  break;		  case 3:  ngen_quark++;  break;		  case 4:  ngen_quark++;  break;		  case 5:  ngen_quark++;  break;		  case 6:  ngen_quark++;  break;				  case 11: ngen_electron++; break;		  case 13: ngen_muon++;     break;		  case 12: case 14: case 16:  break;		}	      }	    }	}    }    }void Fork_Subsample::CountLeptons_DY(){  for(size_t i = 0; i < input_event -> gen.size(); ++ i)     {      const reco::GenParticle & p = input_event -> gen[i];      int id_p   = p.pdgId();         //select Z      if(abs(id_p) != 23 && abs(id_p)!=22) continue;         if( p.status()!=3) continue;	  	        for(size_t b = 0; b < p.numberOfDaughters(); ++ b)	{	  int id_d = abs (p.daughter(b)->pdgId());	  if(id_d == 11) { ngen_electron ++;  }	  if(id_d == 13) { ngen_muon ++; }	  if(id_d == 15) { ngen_tau++; }	}    }	/*	printf("el %u mu %u tau %u\n", ngen_electron, ngen_muon, ngen_tau);		getchar();*/}bool Fork_Subsample::CheckGeneric() const{  return true;}/*TH1D * const Fork_Subsample::GetStatisticsHistogram(const unsigned short sample_ind) const{   return (TH1D*)hstruct_worker -> GetHStructure(samples_names[sample_ind], "numb_events_selection_stagesCHANNELGATE") -> GetPtr();   }void Fork_Subsample::CollectStatistics(){    TH1D * const h = GetStatisticsHistogram(number_active_sample);   const double weight = 1;  h -> Fill(Fork_Subsample_report_Xaxis_labels[0], weight);  if (PassedCleaning)    h -> Fill(Fork_Subsample_report_Xaxis_labels[1], weight); else return;  if (LeptonCorresponds)    h -> Fill(Fork_Subsample_report_Xaxis_labels[2], weight); else return;  if (Trigger_Fired)    h -> Fill(Fork_Subsample_report_Xaxis_labels[3], weight); else return;  if (not OtherTriggersVeto)    h -> Fill(Fork_Subsample_report_Xaxis_labels[4], weight); else return;  if (valid_TTbarMC)    {                  h -> Fill(Fork_Subsample_report_Xaxis_labels[5], weight);           }       }*/void Fork_Subsample::Report(){    printf("Fork subsample received %f passed %f\n", received, passed);  ContinueReportToNextStage();}Fork_Subsample::~Fork_Subsample(){}