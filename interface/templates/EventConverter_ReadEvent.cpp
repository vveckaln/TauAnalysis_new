#include "LIP/TauAnalysis/interface/ReadEvent.hh"
#include "LIP/TauAnalysis/interface/EventConverter.hh"

#include <math.h>
#include "TVectorD.h"
#include "TLorentzVector.h"
#include <iostream>
template<>
EventConverter<ReadEvent>::EventConverter(EventSink<DigestedEvent*> * next_processor_stage): EventProcessor<ReadEvent, DigestedEvent*>(next_processor_stage)
{

}

template<>
void EventConverter<ReadEvent>::Run()
{
  /*output_buffer = new EventBuffer<DigestedEvent*>(10, "dependent");
  for (ulong entry_ind = 0; entry_ind < input_buffer -> size(); entry_ind ++)
  {
    const ReadEvent read_event = (*input_buffer)[entry_ind];
    output_buffer -> GetWriteSlot() = DigestEvent(read_event);
    output_buffer -> PushWriteSlot();
        
    if (output_buffer -> IsFull())
    {
      ProceedToNextStage();
      delete output_buffer;
      output_buffer = new EventBuffer<DigestedEvent*>(10, "dependent");
    }

  } 

  if (!output_buffer -> IsEmpty())
  {
    printf("EventDigester proceeding\n");
    ProceedToNextStage();
    delete output_buffer;

    }*/
}


template<>
void EventConverter<ReadEvent>::Report()
{
  ContinueReportToNextStage();

}

template<>
DigestedEvent* EventConverter<ReadEvent>::ConvertEvent(const ReadEvent & readEvent )
{
  DigestedEvent *brokenDownEvent = new DigestedEvent();
  /*brokenDownEvent -> Open();
  
  for (unsigned char ind = 0; ind < readEvent . leptonsClassifColl -> GetEntries(); ind ++)
  {
    if (fabs((*(TVectorD*)readEvent . leptonsClassifColl -> At(ind))[0]) == 11)
    {
      const Electron electron = Electron((TLorentzVector*)readEvent . leptonsColl -> At(ind), 
					 (TVectorD*) readEvent . leptonsClassifColl -> At(ind));
      brokenDownEvent -> Electrons . push_back(electron);
    } 
      
    if (fabs((*(TVectorD*)readEvent . leptonsClassifColl -> At(ind))[0]) == 13)
    {
      const Muon muon = Muon((TLorentzVector*)readEvent . leptonsColl -> At(ind), 
			     (TVectorD*) readEvent . leptonsClassifColl -> At(ind));
      brokenDownEvent -> Muons . push_back(muon);
    } 
    
    if (fabs((*(TVectorD*)readEvent . leptonsClassifColl -> At(ind))[0]) == 15)
    {
      const Tau tau = Tau((TLorentzVector*)readEvent . leptonsColl -> At(ind), 
			  (TVectorD*) readEvent . leptonsClassifColl -> At(ind));
      brokenDownEvent -> Taus . push_back(tau);
    } 
  }
  
  for (unsigned char jet_ind = 0; jet_ind < readEvent . jetsColl -> GetEntries(); jet_ind++)
  {
    const Jet jet = Jet((TLorentzVector*)readEvent . jetsColl -> At(jet_ind), 
			(TVectorD*) readEvent . jetsClassifColl -> At(jet_ind));
    brokenDownEvent -> Jets . push_back(jet);
  }
  for (unsigned char met_ind = 0; met_ind < readEvent . metColl -> GetEntries(); met_ind ++)
  {
    const MET met = MET((TLorentzVector*)readEvent . metColl -> At(met_ind), 
			(TVectorD*) readEvent . metClassifColl -> At(met_ind));
    brokenDownEvent -> met . push_back(met);
  }

  for (unsigned char vertex_ind = 0; vertex_ind < readEvent . vertexColl -> GetEntries(); vertex_ind ++){
    const Vertex vertex;
    brokenDownEvent -> Vertices . push_back(vertex);
  }
  //printf("muon size %lu electron size %lu tau size %lu\n", brokenDownEvent -> Muons.size(), brokenDownEvent -> Electrons.size(), brokenDownEvent -> Taus.size());*/
  return brokenDownEvent;
}

template<>
EventConverter<ReadEvent>::~EventConverter()
{
}
