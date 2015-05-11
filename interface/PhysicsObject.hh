#ifndef _PhysicsObject_hh
#define _PhysicsObject_hh

#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "TLorentzVector.h"
#include "TVectorD.h"
#include <vector>
using namespace std;

class Object
{
public:
  Object();
  virtual ~Object();
  virtual void ls(const char * = "") const = 0;
};

class PhysicsObject: public Object, public TLorentzVector
{
public:
  PhysicsObject();
  PhysicsObject(const TLorentzVector * const, const TVectorD * const);
  PhysicsObject(const TLorentzVector &);
  PhysicsObject(const LorentzVector );
  PhysicsObject(const LorentzVectorF );
  static const char* title;
  virtual void ls(const char * = "") const = 0;
  virtual void ListLorentzVector() const;
  virtual PhysicsObject &operator += (const TLorentzVector); 
  //PhysicsObject &operator -= (const TLorentzVector &); 
  int idbits;
  virtual ~PhysicsObject();
};

class Lepton: public PhysicsObject
{
public:
  TString title;
  Lepton();
  Lepton(const TLorentzVector * const, const TVectorD * cons);
  Lepton(const LorentzVector);
  Lepton(const LorentzVectorF);
  virtual void ls(const char* = "") const;
  //virtual void ListLorentzVector() const;

  float d0;
  float dZ;
  char charge;
  double relative_isolation;
  int idbits;
  virtual ~Lepton();
};

class Electron: public Lepton
{
public:
  static const char* title;
  Electron();
  Electron(const TLorentzVector * const, const TVectorD * const);
  Electron(const llvvLepton);
  virtual void ls(const char * = "") const;
  virtual void ListLorentzVector() const;

  struct 
  {
    float mvatrigv0;
    float sceta;
    bool  isConv;
  } el_info;
  
  virtual ~Electron() = default;
  
};

class Muon: public Lepton
{
public:
  static const char * title;
  Muon();
  Muon(const TLorentzVector * const, const TVectorD * const);
  Muon(const llvvLepton);

  virtual void ls(const char * = "") const;
  virtual ~Muon() = default;
};

class Tau: public Lepton
{
public:
  static const char * title;
  Tau();
  Tau(const TLorentzVector * const, const TVectorD * const);
  Tau(const llvvTau);
  vector<TLorentzVector> tracks;
  bool passID(const uint64_t IdBit) const;
  unsigned long idbits;
  bool isPF;
  float emfraction;
  void ls_tracks() const;
  virtual void ls(const char * = "") const;
  virtual ~Tau() =  default;
};

class Jet: public PhysicsObject
{
public:
  Jet();
  Jet(const TLorentzVector * const, const TVectorD * const);
  Jet(const llvvJetExt);
  double GetPt() const;
  virtual void ls(const char * = "") const;
  bool   BTagSFUtil_isBtagged;
  double genJetPt;
  int    genflav;
  double CSV_discriminator;
  double jetpgid;
  bool   isBtagged;
  float  torawsf, area;
  virtual ~Jet() = default;
};

class MET: public PhysicsObject
{
public:
  MET();
  MET(const TLorentzVector * const, const TVectorD *const);
  MET(const TLorentzVector &);
  MET(const llvvMet);
  virtual void ls(const char * = "") const;
  virtual ~MET() = default;
};

class Vertex: public Object
{
public:
  Vertex() = default;
  virtual void ls(const char * = "") const;
  virtual ~Vertex() = default;
};

#endif

