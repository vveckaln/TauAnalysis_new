#include "LIP/TauAnalysis/interface/HistogramFiller.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"

#include <math.h>
using namespace cpHistogramPoolRegister;

HistogramFiller::HistogramFiller(EventSink<PureEvent *> *next_processor_stage) : 
  EventProcessor<PureEvent*, PureEvent *>(next_processor_stage)
{
  
}

void HistogramFiller::Run()
{
  
  output_buffer = input_buffer;
  for (unsigned char ind = 0; ind < input_buffer -> size(); ind ++)
    { 
      FillHistograms();
      const PureEvent * event = (*input_buffer)[ind];
      ((TH1D*)hstruct_worker -> GetHStructure(samples_names[number_active_sample], "Pt_tau") -> GetPtr()) -> Fill(event -> tau . Pt(), event -> pileup_corr_weight);
      ((TH1D*)hstruct_worker -> GetHStructure(samples_names[number_active_sample], "eta_tau") -> GetPtr()) -> Fill(event -> tau . Eta(), event -> pileup_corr_weight);
      event -> tau.ls_tracks();
      getchar();
      //printf("%f\n", 1);
      /*if (number_active_sample == 1)
	w += event -> pileup_corr_weight;*/
    }
}

void HistogramFiller::Report()
{
  printf("weight %f\n", w);
}

void HistogramFiller::FillHistograms()
{
  /* histogram_pool -> Fill_Delta_R_lepton_1st_leading_jet();
  histogram_pool -> Fill_Abs_Delta_phi_lepton_MET();
  histogram_pool -> Fill_eta_tau();*/
}

HistogramFiller::~HistogramFiller()
{
}
