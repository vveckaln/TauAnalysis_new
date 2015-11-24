#ifndef _Preselector_Leptons_hh
#define _Preselector_Leptons_hh
#include "CERN_RTU/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "CERN_RTU/TauAnalysis/interface/EventProcessor.hh"
#include "CERN_RTU/TauAnalysis/interface/Register.hh"
#include "CERN_RTU/TauAnalysis/interface/SamplesCatalogue.hh"

#include "CERN_RTU/TauAnalysis/interface/test_utilities.hh"

#include "TH1F.h"
using namespace cpregister;
#ifdef event_type
#undef event_type
#endif
#define event_type ReadEvent_llvv * 

class Preselector_Leptons : public EventProcessor<event_type, event_type> 
{
  bool print_mode;
  double selected;
  vector<pat::Muon*>         muons_ptr;
  vector<pat::Electron*>     electrons_ptr;
  pat::Electron * electron;
  reco::Vertex  * vtx;
  EventBuffer<event_type>::iterator it;

  unsigned int PreselectMuons() ;
  unsigned int PreselectElectrons() ;

  unsigned int VetoLooseElectrons();
  unsigned int VetoLooseMuons();
  bool passIdElectron(const unsigned char IdLevel) const;

  void FinalSelection() const;
  
public:
  Preselector_Leptons(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Preselector_Leptons();

};


#endif
