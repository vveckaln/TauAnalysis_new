#ifndef _Preselector_hh
#define _Preselector_hh
#include "TauAnalysis/interface/ReadEvent_llvv.hh"
#include "TauAnalysis/interface/EventProcessor.hh"
#include "TauAnalysis/interface/Register.hh"
#include "TauAnalysis/interface/SamplesCatalogue.hh"

#include "TauAnalysis/interface/test_utilities.hh"

#include "TH1F.h"
using namespace cpregister;
typedef ReadEvent_llvv event_type;
class Preselector : public EventProcessor<event_type, event_type> 
{
  bool print_mode;
  
  event_type * processed_event;
  void PreselectElectrons() const;
  void PreselectMuons() const;
  void PreselectTaus() const;
  void PreselectJets() const;
  
public:
  Preselector(EventSink<event_type> *next_processor_stage);
  void Run();
  void Report();
  virtual ~Preselector();

};
#endif
