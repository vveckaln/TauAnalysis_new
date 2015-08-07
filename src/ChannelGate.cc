#include "LIP/TauAnalysis/interface/ChannelGate.hh"#include "LIP/TauAnalysis/interface/GlobalVariables.hh"#include "LIP/TauAnalysis/interface/Parser.hh"#include "LIP/TauAnalysis/interface/Register.hh"#include "LIP/TauAnalysis/interface/HStructure_worker.hh"#include <math.h>#include "TCanvas.h"using namespace cpregister;using namespace gVariables;const short ChannelGate::report_size = 6;const char *ChannelGate::ChannelGate_report_Xaxis_labels[report_size] =     {      "received in total",      "passed cleaning",       "leading lepton selection",      "trigger fired (received in channel)",      "other triggers veto",       "valid TTbarMC"    };ChannelGate::ChannelGate(EventSink<DigestedEvent *> *next_processor_stage):EventProcessor<DigestedEvent*, DigestedEvent *>(next_processor_stage){  for (unsigned short sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)    {      TH1D * h = GetStatisticsHistogram(sample_ind);       h -> SetBit(TH1::kCanRebin);      TAxis *xaxis = h -> GetXaxis();      for (int binind = 1; binind <= xaxis -> GetNbins(); binind ++)	{	  xaxis -> SetBinLabel(binind, ChannelGate_report_Xaxis_labels[binind - 1]);	}    }    if (IsGeneric) SetEnvironment_generic();  if (IsDY) SetEnvironment_DY();  if (IstW) SetEnvironment_TTbarMC();  if (IsTTbarMC) SetEnvironment_TTbarMC();}void ChannelGate::Run(){  output_buffer = new EventBuffer<DigestedEvent*>(10);  for (unsigned char ind = 0; ind < input_buffer -> size(); ind ++)    {       //printf("new event\n");      processed_event     = (*input_buffer)[ind];      processed_event -> ngenElectronStatus3 = 0;      processed_event -> ngenMuonStatus3 = 0;      processed_event -> ngenTauStatus3 = 0;      for(size_t igen = 0; igen < processed_event -> gen.size(); igen++)	{	  if(processed_event -> gen[igen].status != 3) continue;	  const int absid = abs(processed_event -> gen[igen].id);	  if (absid == 11) processed_event -> ngenElectronStatus3 ++;	  if (absid == 13) processed_event -> ngenMuonStatus3 ++;	  	  if (absid == 15) 	    {	      double DeltaR_electron = 100;	      double DeltaR_muon = 100;	      llvvGenParticle *g = &processed_event -> gen[igen];	      TLorentzVector test(g->Px(), g->Py(), g->Pz(), g-> energy()); 	      for (unsigned char el_ind = 0; el_ind < processed_event -> Electrons.size(); el_ind ++)		{		  if (processed_event -> ValidateElectron(el_ind))		    {		      double DeltaR = processed_event -> Electrons[el_ind] . DeltaR(test);		      if (DeltaR < DeltaR_electron)			DeltaR_electron = DeltaR;		    }		}	      for (unsigned char mu_ind = 0; mu_ind < processed_event -> Muons.size(); mu_ind ++)		{		  if (processed_event -> ValidateMuon(mu_ind))		    {      		      double DeltaR = processed_event -> Muons[mu_ind] . DeltaR(test);		      if (DeltaR < DeltaR_muon)			DeltaR_muon = DeltaR;		    }		}	      double DeltaR_check;	      unsigned char *corr_count; 	      if(DeltaR_muon < DeltaR_electron)		{		  DeltaR_check = DeltaR_muon;		  corr_count = &processed_event -> ngenMuonStatus3;		}	      else		{		  DeltaR_check = DeltaR_electron;		  corr_count = &processed_event -> ngenElectronStatus3;		}	      if (DeltaR_check < 0.3)		{		  		  (*corr_count) ++;		  //printf("%u %u\n", processed_event -> ngenMuonStatus3, processed_event -> ngenElectronStatus3);		  //getchar();		}	      else		{		  processed_event -> ngenTauStatus3 ++;		}	    }	}      geChONmuChOFF       = false;      bool channel_opened = ChannelOpened();            /*printf("EVENT IDENTITY %u %u %u\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event);      processed_event -> ls("electron", "verbose");      processed_event -> ls("muon", "verbose");      printf("Event passed quality cleaning       %s\n", PassedCleaning ? "true" : "false");      printf("Leading lepton is a muon            %s\n", LeptonCorresponds ? "true" : "false");      printf("Muon trigger fired                  %s\n", Trigger_Fired ? "true" : "false");      printf("Event was selected for muon channel %s\n", channel_opened ? "true" : "false");      printf("---------------- NEXT -----------------------\n");*/      CollectStatistics();      if (channel_opened) 	{	  //getchar();	  output_buffer -> GetWriteSlot() = processed_event;      	  output_buffer -> PushWriteSlot();	}      if (output_buffer -> IsFull())	{	  ProceedToNextStage();	  delete output_buffer;	  output_buffer = new EventBuffer<DigestedEvent*>(10);	}    }  if (!output_buffer -> IsEmpty())    {      ProceedToNextStage();      delete output_buffer;     }}bool ChannelGate::ChannelOpened(){  PassedCleaning    = processed_event -> GetLeadingLepton("electronmuon") != NULL;  LeptonCorresponds = CheckLeadingLepton();      Trigger_Fired     = TriggerFired();  OtherTriggersVeto = VetoAdditionalTriggers();  valid_TTbarMC     = (this ->* sample_check_ptr[number_active_sample])();  return PassedCleaning and LeptonCorresponds and Trigger_Fired and not OtherTriggersVeto and valid_TTbarMC;}bool ChannelGate::CheckLeadingLepton() const{  const Lepton * const lepton = processed_event -> GetLeadingLepton("electronmuon");  bool LeptonCorresponds = false;  if (lepton == NULL) return false;  if (lepton -> title == "muon")    LeptonCorresponds = not geChONmuChOFF;     if (lepton -> title == "electron")     LeptonCorresponds = geChONmuChOFF;    return LeptonCorresponds;}bool ChannelGate::TriggerFired() const{  if (not geChONmuChOFF)    {      const bool muon_trigger(processed_event -> triggerBits[6]);      if (muon_trigger) return true;    }  return false;}bool ChannelGate::VetoAdditionalTriggers() const{  bool filterOnlyEE(false), filterOnlyMUMU(false), filterOnlyEMU(false), filterOnlySINGLEMU(false);    if(not gIsData)    {      filterOnlyEE       = input_file_name.Contains("DoubleEle");       filterOnlyMUMU     = input_file_name.Contains("DoubleMu");       filterOnlyEMU      = input_file_name.Contains("MuEG");       filterOnlySINGLEMU = input_file_name.Contains("SingleMu");     }  bool eeTrigger   = processed_event -> triggerBits[0];  bool emuTrigger  = processed_event -> triggerBits[4] || processed_event -> triggerBits[5];  bool mumuTrigger = processed_event -> triggerBits[2] || processed_event -> triggerBits[3];  if(filterOnlyEE)       {                    emuTrigger = false; mumuTrigger = false; }  if(filterOnlyEMU)      { eeTrigger = false;                     mumuTrigger = false; }  if(filterOnlyMUMU)     { eeTrigger = false; emuTrigger = false;                      }  if(filterOnlySINGLEMU) { eeTrigger = false; emuTrigger = false; mumuTrigger = false; }  const bool otherTriggersVeto( eeTrigger || emuTrigger || mumuTrigger );   return otherTriggersVeto;}bool ChannelGate::IsLowQualityEvent() const{  if (processed_event -> Electrons.size() == 0 and      processed_event -> Muons.size() == 0) return true;  return false;}bool ChannelGate::CheckTTbarMC_muon_tau() const{  if(processed_event -> ngenTauStatus3 == 1      and processed_event -> ngenMuonStatus3 == 1      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_lepton_jets() const{  if(processed_event -> ngenTauStatus3 == 0      and (processed_event -> ngenMuonStatus3 + 	  processed_event -> ngenElectronStatus3) >= 1      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_dilepton_muon_electron() const{  if(processed_event -> ngenTauStatus3 == 0      and processed_event -> ngenMuonStatus3 >= 1      and processed_event -> ngenElectronStatus3 >= 1      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_dilepton_muon_muon() const{  if(processed_event -> ngenTauStatus3 == 0      and processed_event -> ngenMuonStatus3 >= 2      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_tau_jets() const{  if(processed_event -> ngenTauStatus3 == 1      and processed_event -> ngenMuonStatus3 == 0      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_tau_tau() const{  if(processed_event -> ngenTauStatus3 == 2      and processed_event -> ngenMuonStatus3 == 0      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_hadronic() const{  if(processed_event -> ngenTauStatus3 == 0      and processed_event -> ngenMuonStatus3 == 0      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckDY_lepton_lepton() const{  if(processed_event -> ngenTauStatus3 == 0      and (processed_event -> ngenMuonStatus3 + 	  processed_event -> ngenElectronStatus3) == 2)     return true;  else return false;}bool ChannelGate::CheckDY_tau_tau() const{  if(processed_event -> ngenTauStatus3 == 2      and processed_event -> ngenMuonStatus3 == 0      and processed_event -> ngenElectronStatus3 == 0)     return true;  else return false;}void ChannelGate::SetEnvironment_TTbarMC() {  typedef bool (ChannelGate::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &ChannelGate::CheckTTbarMC_muon_tau,       &ChannelGate::CheckTTbarMC_lepton_jets,       &ChannelGate::CheckTTbarMC_dilepton_muon_electron,       &ChannelGate::CheckTTbarMC_dilepton_muon_muon,      &ChannelGate::CheckTTbarMC_tau_jets,      &ChannelGate::CheckTTbarMC_tau_tau,      &ChannelGate::CheckTTbarMC_hadronic,     };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}void ChannelGate::SetEnvironment_DY() {  typedef bool (ChannelGate::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &ChannelGate::CheckDY_lepton_lepton,       &ChannelGate::CheckDY_tau_tau         };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}void ChannelGate::SetEnvironment_generic() {  typedef bool (ChannelGate::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &ChannelGate::CheckGeneric     };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}bool ChannelGate::CheckGeneric() const{  return true;}TH1D * const ChannelGate::GetStatisticsHistogram(const unsigned short sample_ind) const{   return (TH1D*)hstruct_worker -> GetHStructure(samples_names[sample_ind], "numb_events_selection_stagesCHANNELGATE") -> GetPtr();   }void ChannelGate::CollectStatistics(){    TH1D * const h = GetStatisticsHistogram(number_active_sample);   const double weight = 1;  h -> Fill(ChannelGate_report_Xaxis_labels[0], weight);  if (PassedCleaning)    h -> Fill(ChannelGate_report_Xaxis_labels[1], weight); else return;  if (LeptonCorresponds)    h -> Fill(ChannelGate_report_Xaxis_labels[2], weight); else return;  if (Trigger_Fired)    h -> Fill(ChannelGate_report_Xaxis_labels[3], weight); else return;  if (not OtherTriggersVeto)    h -> Fill(ChannelGate_report_Xaxis_labels[4], weight); else return;  if (valid_TTbarMC)    {                  h -> Fill(ChannelGate_report_Xaxis_labels[5], weight);           }   }void ChannelGate::Report(){  for (unsigned short sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)    {      printf("ChannelGate report %s\n", samples_names[sample_ind].Data());      TH1D * const h = GetStatisticsHistogram(sample_ind);      //h -> LabelsDeflate();      printf("number of bins %u %s\n", h -> GetNbinsX(), h -> GetName());       for (ushort bin_ind = 1; bin_ind <= h -> GetNbinsX(); bin_ind++)	{	  printf("%u, %s %u\n", bin_ind, 		 h -> GetXaxis() -> GetBinLabel(bin_ind), 		 (int)h -> GetBinContent(bin_ind));	}    }    ContinueReportToNextStage();}ChannelGate::~ChannelGate(){}