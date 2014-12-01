#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "LIP/TauAnalysis/interface/EventConverter.hh"
#include "LIP/TauAnalysis/interface/MacroUtils.h"

#include <math.h>
#include "TVectorD.h"
#include "TLorentzVector.h"
#include <iostream>

template<class InputEvent>
DigestedEvent * EventConverter<InputEvent>::ConvertEvent(const InputEvent * const)
{
  return new DigestedEvent();
}

template<>
EventConverter<ReadEvent_llvv>::EventConverter(EventSink<DigestedEvent*> * next_processor_stage): EventProcessor<ReadEvent_llvv, DigestedEvent*>(next_processor_stage)
{

}

template<>
void EventConverter<ReadEvent_llvv>::Run()
{
  output_buffer = new EventBuffer<DigestedEvent*>(10, "dependent");
  for (ulong entry_ind = 0; entry_ind < input_buffer -> size(); entry_ind ++)
  {
    const ReadEvent_llvv * const read_event = &(*input_buffer)[entry_ind];
    
    output_buffer -> GetWriteSlot() = ConvertEvent(read_event);
    output_buffer -> PushWriteSlot();

    if (output_buffer -> IsFull())
    {
      ProceedToNextStage();
      delete output_buffer;
      output_buffer = NULL;
      //output_buffer = new EventBuffer<DigestedEvent*>(10, "dependent");
    }

  } 

  if (output_buffer != NULL)
    {
    if (!output_buffer -> IsEmpty())
      {
	printf("EventDigester proceeding\n");
	ProceedToNextStage();
	delete output_buffer;

      }
    }
}


template<>
void EventConverter<ReadEvent_llvv>::Report()
{
  ContinueReportToNextStage();

}

template<>
DigestedEvent* EventConverter<ReadEvent_llvv>::ConvertEvent(const ReadEvent_llvv * const read_event )
{
  DigestedEvent *brokenDownEvent = new DigestedEvent();
  
  for (unsigned int lepton_ind = 0; lepton_ind < read_event -> leptons.size(); lepton_ind ++)
    {
      const double relative_isolation = utils::cmssw::relIso(&read_event -> leptons[lepton_ind], read_event -> rho);
      if (abs(read_event -> leptons[lepton_ind].id) == 11)
	{
	  Electron electron(read_event -> leptons[lepton_ind]);
	  electron.relative_isolation = relative_isolation;
	  brokenDownEvent -> Electrons . push_back( electron );
	  
	} 

      if (abs(read_event -> leptons[lepton_ind].id) == 13)
	{
	  Muon muon( Muon(read_event -> leptons[lepton_ind]));
	  muon . relative_isolation = relative_isolation;
	  brokenDownEvent -> Muons . push_back( muon);
	} 

    }    
  for(unsigned int tau_ind = 0; tau_ind < read_event -> taus.size(); tau_ind ++)
    {
      brokenDownEvent -> Taus.push_back( Tau(read_event -> taus[tau_ind]) );
    }  
    

  for(unsigned int jet_ind = 0; jet_ind < read_event -> jets . size(); jet_ind ++)
    {
      Jet jet( read_event -> jets[jet_ind]);
      jet . CSV_discriminator = read_event -> jets[jet_ind].csv;
      jet. genflav = read_event -> jets[jet_ind] . genflav;
      jet. torawsf = read_event -> jets[jet_ind]. torawsf;
      jet. area = read_event -> jets[jet_ind]. area;

      brokenDownEvent -> Jets.push_back( jet );
    }  
    
  brokenDownEvent -> met . push_back( MET(read_event -> met) );
  brokenDownEvent -> triggerBits = read_event -> triggerBits;
  brokenDownEvent -> rho = read_event -> rho;
  brokenDownEvent -> ngenITpu = read_event -> genEv.ngenITpu;
  return brokenDownEvent;
}

template<>
EventConverter<ReadEvent_llvv>::~EventConverter()
{
}
