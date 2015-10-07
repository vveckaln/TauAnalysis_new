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
  output_buffer = new EventBuffer<DigestedEvent*>(10, "independent");
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
	  electron.relative_isolation   = relative_isolation;
	  electron.idbits               = read_event -> leptons[lepton_ind].idbits;
	  electron.dZ                   = read_event -> leptons[lepton_ind].dZ;
	  electron.d0                   = read_event -> leptons[lepton_ind].d0;
	  electron.el_info.isConv       = read_event -> leptons[lepton_ind].el_info.isConv;
	  electron.el_info.mvatrigv0    = read_event -> leptons[lepton_ind].el_info.mvatrigv0;
	  electron.el_info.sceta        = read_event -> leptons[lepton_ind].el_info.sceta;
	  /*printf("Converter IsConv %s %s\n", electron.el_info.isConv ? "true" : "false", read_event -> leptons[lepton_ind].el_info.isConv ? "true" : "false");
	   printf("Converter mvatrigv0 %f %f\n", electron.el_info.mvatrigv0, read_event->leptons[lepton_ind].el_info.mvatrigv0);
	   printf("Converter sceta %f %f\n",  electron.el_info.sceta,        read_event->leptons[lepton_ind].el_info.sceta);*/
	  brokenDownEvent -> Electrons . push_back( electron );
	  
	} 

      if (abs(read_event -> leptons[lepton_ind].id) == 13)
	{
	  Muon muon( Muon(read_event -> leptons[lepton_ind]));
	  muon.dZ                   = read_event -> leptons[lepton_ind].dZ;
	  muon.d0                   = read_event -> leptons[lepton_ind].d0;
	  muon . relative_isolation = relative_isolation;
	  muon.idbits = read_event -> leptons[lepton_ind].idbits;
	  brokenDownEvent -> Muons . push_back( muon);
	} 

    }    
  for(unsigned int tau_ind = 0; tau_ind < read_event -> taus.size(); tau_ind ++)
    {
      Tau tau( Tau(read_event -> taus[tau_ind]) );
      tau.idbits     = read_event -> taus[tau_ind].idbits;
      tau.isPF       = read_event -> taus[tau_ind].isPF;
      tau.dZ         = read_event -> taus[tau_ind].dZ;
      tau.emfraction = read_event -> taus[tau_ind].emfraction;
      for (unsigned int ind = 0; ind < read_event -> taus[tau_ind].tracks.size(); ind ++)
	{
	  const LorentzVectorF * const l = & read_event -> taus[tau_ind].tracks[ind];
	  tau.tracks.push_back(TLorentzVector(l -> Px(), l -> Py(), l -> Pz(), l -> E()));
	}
      brokenDownEvent -> Taus.push_back( tau );
    }  
    

  for(unsigned int jet_ind = 0; jet_ind < read_event -> jets . size(); jet_ind ++)
    {
      Jet jet( read_event -> jets[jet_ind]);
      jet. CSV_discriminator   = read_event -> jets[jet_ind].csv;
      jet. genflav = read_event -> jets[jet_ind]. genflav;
      jet. torawsf = read_event -> jets[jet_ind]. torawsf;
      jet. area    = read_event -> jets[jet_ind]. area;
      jet. idbits  = read_event -> jets[jet_ind]. idbits;
      brokenDownEvent -> Jets.push_back( jet );
    }  
    
  brokenDownEvent -> met . push_back( MET(read_event -> met) );
  brokenDownEvent -> triggerBits = read_event -> triggerBits;
  brokenDownEvent -> rho         = read_event -> rho;
  brokenDownEvent -> ngenITpu    = read_event -> genEv.ngenITpu;
  brokenDownEvent -> Run         = read_event -> Run;
  brokenDownEvent -> Lumi        = read_event -> Lumi;
  brokenDownEvent -> Event       = read_event -> Event;
  
  brokenDownEvent -> hasTop              = false;
  brokenDownEvent -> ngenElectronStatus3 = 0;
  brokenDownEvent -> ngenMuonStatus3     = 0;
  brokenDownEvent -> ngenTauStatus3      = 0;
  brokenDownEvent -> tPt                 = 0;
  brokenDownEvent -> tbarPt              = 0;
  if(not gIsData)
    {
      for(size_t igen = 0; igen < read_event -> gen.size(); igen++)
	{
	  if(read_event -> gen[igen].status != 3) continue;
	  const int absid = abs(read_event -> gen[igen].id);
	  if(absid == 6)
	    {
	      brokenDownEvent -> hasTop = true;
	      if(IsTTbarMC)
		{
		  if(read_event -> gen[igen].id > 0) 
		    brokenDownEvent -> tPt = read_event -> gen[igen].pt();
		  else 
		    brokenDownEvent -> tbarPt = read_event -> gen[igen].pt();
		}
	      
	    }
	  if (absid == 11) brokenDownEvent -> ngenElectronStatus3 ++;
	  if (absid == 13) brokenDownEvent -> ngenMuonStatus3 ++;
	  if (absid == 15) brokenDownEvent -> ngenTauStatus3 ++;
	}
      //printf("ngenLeptonsStatus3 =%u\n", brokenDownEvent -> ngenLeptonsStatus3); 
    }
  brokenDownEvent -> gen = read_event -> gen;
  //printf("%u %lu\n", brokenDownEvent -> GetObjectCount("all"), read_event -> gen.size());
  //getchar();
  return brokenDownEvent;
}

template<>
EventConverter<ReadEvent_llvv>::~EventConverter()
{
}
