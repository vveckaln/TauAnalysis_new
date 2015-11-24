#include "TauAnalysis/interface/Preselector_MET.hh"
#include "TauAnalysis/interface/GlobalVariables.hh"
#include "TauAnalysis/interface/HStructure_worker.hh"
#include "TauAnalysis/interface/Register.hh"

#include "TauAnalysis/interface/llvvObjects.h"
#include "TauAnalysis/interface/Table.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "TauAnalysis/interface/GlobalVariables.hh"
#include "TauAnalysis/interface/PatUtils.h"
#include "TauAnalysis/interface/Utilities.hh"

#include <math.h>
#include "TCanvas.h"
using namespace gVariables;



Preselector_MET::Preselector_MET(EventSink<event_type> *next_processor_stage) : EventProcessor<event_type, event_type>(next_processor_stage)
{
  selected = 0;
  selected2 = 0;
}

void Preselector_MET::Run()
{
  output_event = input_event;
  selected += input_event -> weight;;   
  TH1D * const h = utilities::GetStatisticsHistogram(number_active_sample);
  h -> Fill("1 lepton, 2 jets, 1 #tau", input_event -> weight); 
  print_mode = false;
  //Run 190688, lumi 99, evId 22420320
  if (input_event -> MET[0].pt() < 40)
    return;

  //if (processed_event -> Run == 190688 and processed_event -> Lumi == 99 and processed_event -> Event == 22420320) print_mode = true;
  //if (not print_mode) continue;
       
  if (print_mode)
    {
      printf("EVENT IDENTITY %u %u %llu\n", input_event -> Run, input_event -> Lumi, input_event -> Event);
	  
    }
  selected2 += input_event -> weight;
  h -> Fill("E^{miss}_{T}", input_event -> weight); 

  ProceedToNextStage();

}


void Preselector_MET::Report()
{
  /*printf ("1 lepton and 3 jets %f\n", selected);
    printf("MET %f\n", selected2);*/
  ContinueReportToNextStage();
}

Preselector_MET::~Preselector_MET()
{
}
