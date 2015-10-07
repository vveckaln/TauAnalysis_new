#include "LIP/TauAnalysis/interface/Fork.hh"
//using namespace cpHistogramPoolRegister;


Fork::Fork(EventSink<DigestedEvent *> *next_processor_stage) :
EventProcessor<DigestedEvent *, DigestedEvent *>(next_processor_stage)
{
  fork_activated = false;
}

void Fork::Run()
{
   
  for (unsigned short sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)
    {
      number_active_sample = sample_ind;
      fork_activated = false;
      if (sample_ind < *number_of_samples - 1) fork_activated = true;
      if(fork_activated)
	{
	  output_buffer = new EventBuffer<DigestedEvent*>(input_buffer);

	}
      else
	output_buffer = input_buffer;
  
      if (!output_buffer -> IsEmpty())
	{
	  ProceedToNextStage();
	  if (fork_activated) delete output_buffer;
	}
    }
}

void Fork::Report()
{
  ContinueReportToNextStage();
}

Fork::~Fork()
{
}
