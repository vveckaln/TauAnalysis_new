#ifndef _PureEvent_hh
#define _PureEvent_hh

#include "CERN_RTU/TauAnalysis/interface/PhysicsObject.hh"
#include "CERN_RTU/TauAnalysis/interface/Event.hh"
#include <vector>
using namespace std;
class PureEvent: public Event
{
  double GetJetPt(const uint i) const;// {return Jets[i] . Pt();};
  double GetJetBtag(const uint i) const {return Jets[i] . CSV_discriminator;};
public:
  Lepton lepton;
  Tau tau;
  vector<Vertex> Vertices;
  vector<Jet> Jets;
  MET met;
  double pileup_corr_weight;

  PureEvent();
  ~PureEvent();
  void ls(const char *) const;
  void Open();
  void Close();
  unsigned int GetLeptonSize();
  unsigned char GetBtagCount() const;
  Lepton * GetLeadingLepton() const;
  Jet * GetLeadingJet(const char *, const int = 1) const;
  //***** pile-up correction results ***
 
  void Print4VectorSum() const;
};

#endif
