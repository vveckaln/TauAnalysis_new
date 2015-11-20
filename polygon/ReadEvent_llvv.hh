#ifndef _ReadEvent_llvv_hh
#define _ReadEvent_llvv_hh
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "LIP/TauAnalysis/interface/Event.hh"
#include <vector>
using namespace std;
class ReadEvent_llvv: public Event
{
public:
  unsigned int                Run;
  unsigned int                Lumi;
  unsigned int                Event;
  reco::VertexCollection      vertices;
  reco::GenParticleCollection genEv;
  pat::MuonCollection         muons;
  pat::ElectronCollection     electrons;
  pat::TauCollection          taus; 
  pat::JetCollection          jets;  
  pat::METCollection          MET;  
  double                      rho;
  vector<bool>                triggerBits;
  virtual void Open();
  virtual void Close();
  ReadEvent_llvv();
  virtual ~ReadEvent_llvv();
} ;
#endif
