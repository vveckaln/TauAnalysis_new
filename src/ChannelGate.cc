#include "LIP/TauAnalysis/interface/ChannelGate.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/Parser.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
#include <math.h>
#include "TCanvas.h"
using namespace cpFileRegister;

const short ChannelGate::report_size = 4;
const char *ChannelGate::ChannelGate_report_Xaxis_labels[report_size] = 
    {
      "received in total",
      "passed cleaning", 
      "leading lepton selection",
      "trigger fired (received in channel)",
    };

ChannelGate::ChannelGate(EventSink<DigestedEvent *> *next_processor_stage):EventProcessor<DigestedEvent*, DigestedEvent *>(next_processor_stage)
{
  mapOfChannelGateHistoPools = new MapOfObjectPools<TH1D>();
  vector<HistogramDescriptor> * channelgate_h_descriptors = LoadHistogramDescriptors("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/histogram_specifiers/spec_channelgate_histograms.xml");
  HistogramPool * base_pool = new HistogramPool(channelgate_h_descriptors, "CHANNELGATE");
  base_pool -> SetDirectoryName("CHANNELGATE");
  mapOfChannelGateHistoPools -> Add((ObjectPool<TH1D>*)base_pool);
  //base_pool -> at("numb_events_selection_stages") -> SetBit(TH1::kCanRebin);
  TH1D * h = base_pool -> at("numb_events_selection_stages");// -> SetBit(TH1::kCanRebin);
  TAxis *xaxis = h -> GetXaxis();
  for (int binind = 1; binind <= xaxis -> GetNbins(); binind ++)
    {
      xaxis -> SetBinLabel(binind, ChannelGate_report_Xaxis_labels[binind - 1]);
    }
}

void ChannelGate::Run()
{
  output_buffer = new EventBuffer<DigestedEvent*>(10);
  for (unsigned char ind = 0; ind < input_buffer -> size(); ind ++)
    { 
      processed_event = (*input_buffer)[ind];
      geChONmuChOFF = false;
      bool channel_opened = ChannelOpened();
      /*printf("EVENT IDENTITY %u %u %u\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event);
      processed_event -> ls("electron");
      processed_event -> ls("muon");
      printf("Event passed quality cleaning       %s\n", PassedCleaning ? "true" : "false");
      printf("Leading lepton is a muon            %s\n", LeptonCorresponds ? "true" : "false");
      printf("Muon trigger fired                  %s\n", Trigger_Fired ? "true" : "false");
      printf("Event was selected for muon channel %s\n", channel_opened ? "true" : "false");
      printf("---------------- NEXT -----------------------\n");
      //getchar();*/
      CollectStatistics();
      if (channel_opened) 
	{
	  
	  output_buffer -> GetWriteSlot() = processed_event;
      
	  output_buffer -> PushWriteSlot();
	}
      if (output_buffer -> IsFull())
	{
	  ProceedToNextStage();
	  delete output_buffer;
	  output_buffer = new EventBuffer<DigestedEvent*>(10);
	}
    }
  if (!output_buffer -> IsEmpty())
    {
      ProceedToNextStage();
      delete output_buffer;
     }
}

bool ChannelGate::ChannelOpened()
{
  PassedCleaning = not IsLowQualityEvent();
  LeptonCorresponds = CheckLeadingLepton();    
  Trigger_Fired = TriggerFired();
  return PassedCleaning and LeptonCorresponds and Trigger_Fired;
}

bool ChannelGate::CheckLeadingLepton() const
{
  const Lepton * const lepton = processed_event -> GetLeadingLepton("electronmuon");
  if (lepton == NULL) return false;
  bool LeptonCorresponds = false;
  
  if (lepton -> title == "muon")
    LeptonCorresponds = not geChONmuChOFF; 
  
  if (lepton -> title == "electron") 
    LeptonCorresponds = geChONmuChOFF;
  
  return LeptonCorresponds;
}

bool ChannelGate::TriggerFired() const
{
  if (not geChONmuChOFF)
    {
      const bool muon_trigger(processed_event -> triggerBits[6]);
      if (muon_trigger) return true;
    }
  return false;
}

bool ChannelGate::IsLowQualityEvent() const
{
  if (processed_event -> Electrons.size() == 0 and
      processed_event -> Muons.size() == 0) return true;
  return false;
}

TH1D * const ChannelGate::GetStatisticsHistogram()
{
  const TString title = "CHANNELGATE";
  return mapOfChannelGateHistoPools -> GetObjectPool(title) 
    -> at("numb_events_selection_stages");
}

void ChannelGate::CollectStatistics()
{
  
  TH1D * const h = GetStatisticsHistogram();
  const double weight = 1;
  h -> Fill(ChannelGate_report_Xaxis_labels[0], weight);
  if (PassedCleaning)
    h -> Fill(ChannelGate_report_Xaxis_labels[1], weight); else return;
  if (LeptonCorresponds)
    h -> Fill(ChannelGate_report_Xaxis_labels[2], weight); else return;
  if (Trigger_Fired)
    h -> Fill(ChannelGate_report_Xaxis_labels[3], weight); else return;
   
}

void ChannelGate::Report()
{
  printf("ChannelGate report\n");
  TH1D * const h = GetStatisticsHistogram();
  h -> LabelsDeflate();
  for (ushort bin_ind = 1; bin_ind <= h -> GetNbinsX(); bin_ind++)
    {
      printf("%u, %s %u\n", bin_ind, 
	   h -> GetXaxis() -> GetBinLabel(bin_ind), 
	   (int)h -> GetBinContent(bin_ind));
    }
 
  output_file -> cd();
  h -> Write();
  
  ContinueReportToNextStage();

}



ChannelGate::~ChannelGate()
{
}
