#ifndef _PhysicsObject_hh
#define _PhysicsObject_hh

#include "TLorentzVector.h"
#include "TVectorD.h"


class Object
{
public:
  Object();
  virtual ~Object();
  virtual void ls() const = 0;
};

class PhysicsObject: public Object, public TLorentzVector
{
public:
  PhysicsObject();
  PhysicsObject(TLorentzVector *lorentz_vector, TVectorD *info);
  static const char* title;
  virtual void ls() const = 0;
  virtual void ListLorentzVector() const;
  virtual PhysicsObject &operator += (const TLorentzVector); 
  virtual PhysicsObject &operator -= (const TLorentzVector); 

  virtual ~PhysicsObject();
};

class Lepton: public PhysicsObject
{
public:
  static const char * title;
  Lepton();
  Lepton(TLorentzVector *lorentz_vector, TVectorD *info);
  virtual void ls() const;
  char charge;
  double relative_isolation;
  virtual ~Lepton();
};

class Electron: public Lepton
{
public:
  static const char* title;
  Electron();
  Electron(TLorentzVector *lorentz_vector, TVectorD *info);
  virtual void ls() const;
  double relative_isolation;
  ~Electron();
  
};

class Muon: public Lepton
{
public:
  static const char * title;
  Muon();
  Muon(TLorentzVector *lorentz_vector, TVectorD *info);
  virtual void ls() const;
  double relative_isolation;
  ~Muon();
};

class Tau: public Lepton
{
public:
  static const char * title;
  Tau();
  Tau(TLorentzVector *lorentz_vector, TVectorD *info);
  virtual void ls() const;
  ~Tau();
};

class Jet: public PhysicsObject
{
public:
  Jet();
  Jet(TLorentzVector *lorentz_vector, TVectorD *info);
  double GetPt() const;
  virtual void ls() const;
  bool BTagSFUtil_isBtagged;
  double genJetPt;
  double CSV_discriminator;
  double jetpgid;
  bool isBtagged;
  ~Jet();
};

class MET: public PhysicsObject
{
public:
  MET();
  MET(TLorentzVector *lorentz_vector, TVectorD *info);
  virtual void ls() const;
  ~MET();
};

class Vertex: public Object
{
public:
  Vertex();
  virtual void ls() const;
  virtual ~Vertex();
};

#endif

