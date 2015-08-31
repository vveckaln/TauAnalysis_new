#include "LIP/TauAnalysis/interface/ChannelGate.hh"#include "LIP/TauAnalysis/interface/GlobalVariables.hh"#include "LIP/TauAnalysis/interface/Parser.hh"#include "LIP/TauAnalysis/interface/Register.hh"#include "LIP/TauAnalysis/interface/HStructure_worker.hh"#include <math.h>#include "TCanvas.h"using namespace cpregister;using namespace gVariables;ChannelGate::ChannelGate(EventSink<event_type> *next_processor_stage):EventProcessor<event_type, event_type>(next_processor_stage){    /*if (IsGeneric) SetEnvironment_generic();  if (IsDY) SetEnvironment_DY();  if (IstW) SetEnvironment_TTbarMC();  if (IsTTbarMC) SetEnvironment_TTbarMC();*/  received = 0;   passed = 0;}void ChannelGate::Run(){  output_event = input_event;  received ++;  geChONmuChOFF       = false;  bool channel_opened = ChannelOpened();  if (not channel_opened)    return;  /*printf("EVENT IDENTITY %u %u %u\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event);    processed_event -> ls("electron", "verbose");    processed_event -> ls("muon", "verbose");    printf("Event passed quality cleaning       %s\n", PassedCleaning ? "true" : "false");    printf("Leading lepton is a muon            %s\n", LeptonCorresponds ? "true" : "false");    printf("Muon trigger fired                  %s\n", Trigger_Fired ? "true" : "false");    printf("Event was selected for muon channel %s\n", channel_opened ? "true" : "false");    printf("---------------- NEXT -----------------------\n");*/        passed ++;  ProceedToNextStage();}bool ChannelGate::ChannelOpened(){  LeptonCorresponds = CheckLeadingLepton();      Trigger_Fired     = TriggerFired();  OtherTriggersVeto = VetoAdditionalTriggers();    return LeptonCorresponds and Trigger_Fired and not OtherTriggersVeto;}bool ChannelGate::CheckLeadingLepton(){  if (input_event -> electrons.size() == 1 and geChONmuChOFF)    return true;  else if (input_event -> muons.size() == 1 and not geChONmuChOFF)    return true;  else    return false;}bool ChannelGate::TriggerFired() {  if (not geChONmuChOFF)    {            if (input_event -> muTrigger) return true;    }  return false;}bool ChannelGate::VetoAdditionalTriggers(){  bool filterOnlyEE(false), filterOnlyMUMU(false), filterOnlyEMU(false), filterOnlySINGLEMU(false);    if(not gIsData)    {      filterOnlyEE       = input_file_name.Contains("DoubleEle");       filterOnlyMUMU     = input_file_name.Contains("DoubleMu");       filterOnlyEMU      = input_file_name.Contains("MuEG");       filterOnlySINGLEMU = input_file_name.Contains("SingleMu");     }    if(filterOnlyEE)       {                                   input_event -> emuTrigger = false; input_event -> mumuTrigger = false; }  if(filterOnlyEMU)      { input_event -> eeTrigger = false;                                    input_event -> mumuTrigger = false; }  if(filterOnlyMUMU)     { input_event -> eeTrigger = false; input_event -> emuTrigger = false;                      }  if(filterOnlySINGLEMU) { input_event -> eeTrigger = false; input_event -> emuTrigger = false; input_event -> mumuTrigger = false; }  const bool otherTriggersVeto( input_event -> eeTrigger || input_event -> emuTrigger || input_event -> mumuTrigger );   return otherTriggersVeto;}/*bool ChannelGate::CheckTTbarMC_muon_tau() const{  if(processed_event -> ngenTauStatus3 == 1      and processed_event -> ngenMuonStatus3 == 1      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_lepton_jets() const{  if(processed_event -> ngenTauStatus3 == 0      and (processed_event -> ngenMuonStatus3 + 	  processed_event -> ngenElectronStatus3) >= 1      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_dilepton_muon_electron() const{  if(processed_event -> ngenTauStatus3 == 0      and processed_event -> ngenMuonStatus3 >= 1      and processed_event -> ngenElectronStatus3 >= 1      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_dilepton_muon_muon() const{  if(processed_event -> ngenTauStatus3 == 0      and processed_event -> ngenMuonStatus3 >= 2      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_tau_jets() const{  if(processed_event -> ngenTauStatus3 == 1      and processed_event -> ngenMuonStatus3 == 0      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_tau_tau() const{  if(processed_event -> ngenTauStatus3 == 2      and processed_event -> ngenMuonStatus3 == 0      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckTTbarMC_hadronic() const{  if(processed_event -> ngenTauStatus3 == 0      and processed_event -> ngenMuonStatus3 == 0      and processed_event -> ngenElectronStatus3 == 0      and processed_event -> hasTop) return true;  else return false;}bool ChannelGate::CheckDY_lepton_lepton() const{  if(processed_event -> ngenTauStatus3 == 0      and (processed_event -> ngenMuonStatus3 + 	  processed_event -> ngenElectronStatus3) == 2)     return true;  else return false;}bool ChannelGate::CheckDY_tau_tau() const{  if(processed_event -> ngenTauStatus3 == 2      and processed_event -> ngenMuonStatus3 == 0      and processed_event -> ngenElectronStatus3 == 0)     return true;  else return false;}void ChannelGate::SetEnvironment_TTbarMC() {  typedef bool (ChannelGate::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &ChannelGate::CheckTTbarMC_muon_tau,       &ChannelGate::CheckTTbarMC_lepton_jets,       &ChannelGate::CheckTTbarMC_dilepton_muon_electron,       &ChannelGate::CheckTTbarMC_dilepton_muon_muon,      &ChannelGate::CheckTTbarMC_tau_jets,      &ChannelGate::CheckTTbarMC_tau_tau,      &ChannelGate::CheckTTbarMC_hadronic,     };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}void ChannelGate::SetEnvironment_DY() {  typedef bool (ChannelGate::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &ChannelGate::CheckDY_lepton_lepton,       &ChannelGate::CheckDY_tau_tau         };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}void ChannelGate::SetEnvironment_generic() {  typedef bool (ChannelGate::*type_ptr)() const;  sample_check_ptr = new type_ptr[*number_of_samples];  type_ptr fnc_ptr[] =     {      &ChannelGate::CheckGeneric     };  for (unsigned short fnc_ind = 0; fnc_ind < *number_of_samples; fnc_ind++)    {      sample_check_ptr[fnc_ind] = fnc_ptr[fnc_ind];    }}bool ChannelGate::CheckGeneric() const{  return true;  }*//*TH1D * const ChannelGate::GetStatisticsHistogram(const unsigned short sample_ind) const{   return (TH1D*)hstruct_worker -> GetHStructure(samples_names[sample_ind], "numb_events_selection_stagesCHANNELGATE") -> GetPtr();   }void ChannelGate::CollectStatistics(){    TH1D * const h = GetStatisticsHistogram(number_active_sample);   const double weight = 1;  h -> Fill(ChannelGate_report_Xaxis_labels[0], weight);  if (PassedCleaning)    h -> Fill(ChannelGate_report_Xaxis_labels[1], weight); else return;  if (LeptonCorresponds)    h -> Fill(ChannelGate_report_Xaxis_labels[2], weight); else return;  if (Trigger_Fired)    h -> Fill(ChannelGate_report_Xaxis_labels[3], weight); else return;  if (not OtherTriggersVeto)    h -> Fill(ChannelGate_report_Xaxis_labels[4], weight); else return;  if (valid_TTbarMC)    {                  h -> Fill(ChannelGate_report_Xaxis_labels[5], weight);           }       }*/void ChannelGate::Report(){    printf("Channel received %f passed %f\n", received, passed);  ContinueReportToNextStage();}ChannelGate::~ChannelGate(){}