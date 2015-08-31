#ifndef _ReadEvent_llvv_hh
#define _ReadEvent_llvv_hh
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include <FWCore/Common/interface/TriggerResultsByName.h>
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "LIP/TauAnalysis/interface/Event.hh"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "Rtypes.h"
#include <vector>
using namespace std;

typedef math::XYZTLorentzVector 	LorentzVector;
class ReadEvent_llvv: public Event
{
  const LorentzVector * non_const_object;
  LorentzVector   previous_state;
public:
  unsigned int                Run;
  unsigned int                Lumi;
  unsigned long long          Event;
  bool eeTrigger;
  bool mumuTrigger;
  bool muTrigger;
  bool emuTrigger;
  reco::VertexCollection      vertices;
  reco::GenParticleCollection gen;
  pat::MuonCollection         muons;
  pat::ElectronCollection     electrons;
  pat::TauCollection          taus; 
  pat::JetCollection          jets;  
  pat::METCollection          MET;  
  pat::PhotonCollection       photons;
  vector<PileupSummaryInfo>   PU;
  GenEventInfoProduct         genEventInfo;

  double                      rho;
  float                       weight;
  vector<bool>                triggerBits;
  unsigned int                nbtags = 0;
  virtual void Open();
  virtual void Close();
  ReadEvent_llvv();
  virtual ~ReadEvent_llvv();
  const reco::LeafCandidate * GetConstObject(const char * type, const uint ind) const;
  reco::LeafCandidate * GetLeadingLepton(const char * option) const;
  reco::LeafCandidate * GetObject(const char * type, const uint ind);
  unsigned char GetObjectCount(const char * type) const;
  void CorrectMET();

} ;
#endif
