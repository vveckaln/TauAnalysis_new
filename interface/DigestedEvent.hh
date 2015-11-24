#ifndef _DigestedEvent_hh
#define _DigestedEvent_hh
#include "CERN_RTU/TauAnalysis/interface/llvvObjects.h"
#include "CERN_RTU/TauAnalysis/interface/PhysicsObject.hh"
#include "CERN_RTU/TauAnalysis/interface/Event.hh"
#include <vector>
using namespace std;
class DigestedEvent: public Event
{
  bool             print_mode;
  double GetJetPt(const uint i) const;// const {return Jets[i] . Pt();};
  double GetJetBtag(const uint i) const {return Jets[i] . CSV_discriminator;};
  TLorentzVector * non_const_object;
  TLorentzVector   previous_state;
public:
  unsigned int     Run;
  unsigned int     Lumi;
  unsigned int     Event; 
  vector<Electron> Electrons;
  vector<Muon>     Muons;
  vector<Tau>      Taus;
  vector<Vertex>   Vertices;
  vector<Jet>      Jets;
  vector<MET>      met;
  vector<bool>     triggerBits;
  llvvGenParticleCollection gen;

  float            rho;
  unsigned char    ngenElectronStatus3;
  unsigned char    ngenMuonStatus3;
  unsigned char    ngenTauStatus3;
  bool             hasTop;
  int              ngenITpu;
  double           pileup_corr_weight;
  float            tPt, tbarPt;
  DigestedEvent();
  ~DigestedEvent();
  void ls(const char *, const char * = "") const;
  void Open();
  void Close();
  
  unsigned char GetObjectCount (const char *) const;
  void erase(const char *, const uint);
  unsigned char PurgeIsNaN();
  unsigned char PurgeZeroPt();
  Object *GetObject(const char *, const uint);
  PhysicsObject *GetPhysicsObject(const char *, const uint);
  const Object * GetConstObject(const char *, const uint) const;
  const PhysicsObject *GetConstPhysicsObject(const char *, const uint) const;
  Lepton * GetLeadingLepton(const char*) const;
  Jet * GetLeadingJet(const char *, const int = 1) const;
  void ApplyJetEnergyScale(const uint uncertainty_subsignal) const;
  void CorrectMET();
  void SmearJets();
  void Print4VectorSum() const;
  bool ValidateElectron(const unsigned short electron_ind) const;
  bool ValidateMuon(const unsigned short muon_ind) const;
  bool ValidateTau(const unsigned short tau_ind, const Lepton * const) const;
  bool DeleteTauJet(const Lepton * const lepton);
  bool ValidateJet(const unsigned short jet_ind, const Lepton & lepton) const;
  unsigned short GetBtagCount(const Lepton & lepton) const;
  //***** pile-up correction results ***
  
};

typedef DigestedEvent ConvertedEvent;

#endif
