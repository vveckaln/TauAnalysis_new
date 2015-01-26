#ifndef _ReadEvent_llvv_hh
#define _ReadEvent_llvv_hh
#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "LIP/TauAnalysis/interface/Event.hh"
#include <vector>
using namespace std;
class ReadEvent_llvv: public Event
{
public:
  unsigned int              Run;
  unsigned int              Lumi;
  unsigned int              Event;
  llvvGenEvent              genEv;
  llvvLeptonCollection      leptons; 
  llvvTauCollection         taus;
  llvvJetExtCollection      jets;
  llvvGenParticleCollection gen;
  llvvMet                   met;
  double                    rho;
  vector<bool>              triggerBits;
  virtual void Open();
  virtual void Close();
  ReadEvent_llvv();
  virtual ~ReadEvent_llvv();
} ;
#endif
