#include "LIP/TauAnalysis/interface/Preselector_OS.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"
#include "LIP/TauAnalysis/interface/Register.hh"

#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "LIP/TauAnalysis/interface/Table.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/PatUtils.h"

#include <math.h>
#include "TCanvas.h"
using namespace gVariables;



Preselector_OS::Preselector_OS(EventSink<event_type> *next_processor_stage) : EventProcessor<event_type, event_type>(next_processor_stage)
{
  
}

void Preselector_OS::Run()
{
  output_buffer = input_buffer;
  for (it = input_buffer -> begin(); it != input_buffer -> end(); it ++)
    { 
     
      print_mode = false;
      //Run 190688, lumi 99, evId 22420320
      if (it -> electrons.size() == 1)
	{
	if (it -> electrons[0].pdgId() * it -> taus[0].pdgId() > 0)
	  input_buffer -> erase(it);
	}
      else
	{
	if (it -> muons[0].pdgId() * it -> taus[0].pdgId() > 0)
	  input_buffer -> erase(it);
	}

      //if (processed_event -> Run == 190688 and processed_event -> Lumi == 99 and processed_event -> Event == 22420320) print_mode = true;
      //if (not print_mode) continue;
       
      if (print_mode)
	{
	  printf("EVENT IDENTITY %u %u %u\n", it -> Run, it -> Lumi, it -> Event);
	  
	}
      
      if (output_buffer -> IsFull())
	{
	  ProceedToNextStage();
	  
	}
    }
  if (!output_buffer -> IsEmpty())
    {
      ProceedToNextStage();
     }
}


void Preselector_OS::Report()
{
}

Preselector_OS::~Preselector_OS()
{
}