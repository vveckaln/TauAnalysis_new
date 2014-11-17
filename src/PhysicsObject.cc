#include "LIP/TauAnalysis/interface/PhysicsObject.hh"
#include "LIP/TauAnalysis/interface/spy_data_format.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
using namespace spydataformat;

Object::Object()
{
}

Object::~Object()
{
}

PhysicsObject::PhysicsObject()
{
}

PhysicsObject::PhysicsObject(TLorentzVector *lorentz_vector, TVectorD *info) :
  TLorentzVector(*lorentz_vector)
{
}

void PhysicsObject::ListLorentzVector() const
{
  
  printf("Px = % 11f Py = % 11f Pz = % 11f Pt = % 11f, E = % 11f\n", Px(), Py(), Pz(), Pt(), E());
  if (Pt() == 0)
  {
    printf("Pt() == 0\n");
    getchar();
  }
}

PhysicsObject & PhysicsObject::operator += (const TLorentzVector other)
{
  (TLorentzVector)(*this) += other;
  return *this;
}

PhysicsObject & PhysicsObject::operator -= (const TLorentzVector other)
{
  (TLorentzVector)(*this) -= other;
  return *this;
}

PhysicsObject::~PhysicsObject()
{
}

Lepton::Lepton() :
  PhysicsObject()
{
}

Lepton::Lepton(TLorentzVector *lorentz_vector, TVectorD *info) :
  PhysicsObject(lorentz_vector, info)
{
}

void Lepton::ls() const
{
}


Lepton::~Lepton()
{
}

const char* Electron::title = "electron";

Electron::Electron() :
  Lepton::Lepton()
{
}

Electron::Electron(TLorentzVector *lorentz_vector, TVectorD *info) :
  Lepton(lorentz_vector, info)
{
  charge = (*info)[(char)ElectronInfo::ID] > 0 ? 1 : -1;
  relative_isolation = (*info)[(char)ElectronInfo::REL_ISOLATION];
}

void Electron::ls() const 
{
  ListLorentzVector();
}

Electron::~Electron()
{
}

const char* Muon::title = "muon";


Muon::Muon() :
  Lepton::Lepton()
{
}

Muon::Muon(TLorentzVector *lorentz_vector, TVectorD *info) :
  Lepton(lorentz_vector, info)
{
  charge = (*info)[(char)MuonInfo::ID] > 0 ? 1 : -1;
  relative_isolation = (*info)[(char)MuonInfo::REL_ISOLATION];
}

void Muon::ls() const 
{
  ListLorentzVector();
}


Muon::~Muon()
{
}

const char* Tau::title = "tau";


Tau::Tau() : 
  Lepton()
{
}

Tau::Tau(TLorentzVector *lorentz_vector, TVectorD *info) :
    Lepton(lorentz_vector, info)
{
  charge = (*info)[(char)TauInfo::ID] > 0 ? 1 : -1;
}

void Tau::ls() const 
{
  ListLorentzVector();
}


Tau::~Tau()
{
}

Jet::Jet() :
  PhysicsObject()
{
}

Jet::Jet(TLorentzVector *lorentz_vector, TVectorD *info) :
  PhysicsObject(lorentz_vector, info)
{
  CSV_discriminator = (*info)[(char)JetInfo::BTAG] > 0 ? 1 : -1;
  genJetPt = (*info)[(char)JetInfo::GENJETPT];
  jetpgid = (*info)[(char)JetInfo::JETPGID];
}

double Jet::GetPt() const
{
  /*if (uncertainty_signal != JES) return Pt();
  jetCorrectionUncertainty -> setJetEta( Eta() );
  jetCorrectionUncertainty -> setJetPt( Pt() ); 
  float correction = jetCorrectionUncertainty -> getUncertainty(true);
  if (uncertainty_subsignal == MINUS) correction *= -1;
  return (1 + correction)*Pt();*/
  return -1;
}

void Jet::ls() const 
{
  ListLorentzVector();
}


Jet::~Jet()
{
}

MET::MET() :
  PhysicsObject()
{
}

MET::MET(TLorentzVector *lorentz_vector, TVectorD *info) :
    PhysicsObject(lorentz_vector, info)
{
}

void MET::ls() const 
{
  ListLorentzVector();
}


MET::~MET()
{
}

Vertex::Vertex()
{
}

void Vertex::ls() const
{
}

Vertex::~Vertex()
{
}
