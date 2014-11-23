#ifndef _DigestedEvent_hh
#define _DigestedEvent_hh

#include "LIP/TauAnalysis/interface/PhysicsObject.hh"
#include "LIP/TauAnalysis/interface/Event.hh"
#include <vector>
using namespace std;
class DigestedEvent: public Event
{
  double GetJetPt(const uint i) const;// const {return Jets[i] . Pt();};
  double GetJetBtag(const uint i) const {return Jets[i] . CSV_discriminator;};
  TLorentzVector jet_difference;
public:
  vector<Electron> Electrons;
  vector<Muon> Muons;
  vector<Tau> Taus;
  vector<Vertex> Vertices;
  vector<Jet> Jets;
  vector<MET> met;
  vector<bool> triggerBits;
  DigestedEvent();
  ~DigestedEvent();
  void ls(const char *) const;
  void Open();
  void Close();
  unsigned char GetBtagCount() const;
  unsigned char GetObjectCount (const char *) const;
  void erase(const char *, const uint);
  unsigned char PurgeIsNaN();
  unsigned char PurgeZeroPt();
  Object *GetObject(const char *, const uint) const;
  PhysicsObject *GetPhysicsObject(const char *, const uint) const;
  Lepton * GetLeadingLepton(const char*) const;
  Jet * GetLeadingJet(const char *, const int = 1) const;
  //***** pile-up correction results ***
  void ApplyJetEnergyScale(const uint uncertainty_subsignal) const;
  void CorrectMET();
  void SmearJets();
  void Print4VectorSum() const;
  double pileup_corr_weight;
};

typedef DigestedEvent ConvertedEvent;

#endif