#include "LIP/TauAnalysis/interface/Preselector_OS.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"
#include "LIP/TauAnalysis/interface/Register.hh"

#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "LIP/TauAnalysis/interface/Table.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/PatUtils.h"
#include "LIP/TauAnalysis/interface/Utilities.hh"

#include <math.h>
#include "TCanvas.h"
using namespace gVariables;



Preselector_OS::Preselector_OS(EventSink<event_type> *next_processor_stage) : EventProcessor<event_type, event_type>(next_processor_stage)
{
  selected = 0;
}

void Preselector_OS::Run()
{
  output_event = input_event;
  print_mode = false;
  TH1D * h = utilities::GetStatisticsHistogram(number_active_sample);
  h -> Fill("1#tau", input_event -> weight);

  //Run 190688, lumi 99, evId 22420320
  if (input_event -> electrons.size() == 1)
    {
      if (input_event -> electrons[0].pdgId() * input_event -> taus[0].pdgId() > 0)
	return;
    }
  else
    {
      if (input_event -> muons[0].pdgId() * input_event -> taus[0].pdgId() > 0)
	return;
    }

  //if (processed_event -> Run == 190688 and processed_event -> Lumi == 99 and processed_event -> Event == 22420320) print_mode = true;
  //if (not print_mode) continue;
       
  if (print_mode)
    {
      printf("EVENT IDENTITY %u %u %llu\n", input_event -> Run, input_event -> Lumi, input_event -> Event);
	  
    }

  selected += input_event -> weight;
  h -> Fill("OS", input_event -> weight);
 
  ProceedToNextStage();
}


void Preselector_OS::Report()
{
  //printf("OS selected %f \n", selected);
  for (uint ind = 0; ind < *number_of_samples; ind ++)
    {
      TH1D * h = utilities::GetStatisticsHistogram(ind);
      printf("REPORT sample %s\n", samples_names[ind].Data());
      Table table("Selector_report_SELECTOR_BASE");
      table.FillFromLabeledHistogram(h);
      table.ls();
    }
  ContinueReportToNextStage();
}

Preselector_OS::~Preselector_OS()
{
}
