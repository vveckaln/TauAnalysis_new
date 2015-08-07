#include "LIP/TauAnalysis/interface/PhysicsObject.hh"
#include "LIP/TauAnalysis/interface/spy_data_format.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
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

PhysicsObject::PhysicsObject(const TLorentzVector * const lorentz_vector, const TVectorD * const info) :
  TLorentzVector(*lorentz_vector)
{
}

PhysicsObject::PhysicsObject(const TLorentzVector & tlorentz_vector) : TLorentzVector(tlorentz_vector)
{

}

PhysicsObject::PhysicsObject(const LorentzVector math_lorentz_vector)
{
  TLorentzVector t_lorentz_vector(
				  math_lorentz_vector . Px(),
				  math_lorentz_vector . Py(),
				  math_lorentz_vector . Pz(),
				  math_lorentz_vector . E()
				  );
  *(TLorentzVector*)(this) = t_lorentz_vector;
}

PhysicsObject::PhysicsObject(const LorentzVectorF math_lorentz_vector_f)
{
  TLorentzVector t_lorentz_vector(
				  math_lorentz_vector_f . Px(),
				  math_lorentz_vector_f . Py(),
				  math_lorentz_vector_f . Pz(),
				  math_lorentz_vector_f . E()
				  );
  *(TLorentzVector*)(this) = t_lorentz_vector;
}



void PhysicsObject::ListLorentzVector() const
{
  
  printf("Pt=% 10f E=% 10f Eta=% 10f Phi=% 10f Px=% 10f, Py=% 10f Pz=% 10f\n", Pt(), E(), Eta(), Phi(), Px(), Py(), Pz());
 
}

PhysicsObject & PhysicsObject::operator += (const TLorentzVector other)
{
  (TLorentzVector)(*this) += other;
  return *this;
}

/*PhysicsObject & PhysicsObject::operator -= (const TLorentzVector & other)
{
  *this -= other;
  return *this;
  }*/

PhysicsObject::~PhysicsObject()
{
}

Lepton::Lepton() :
  PhysicsObject()
{
}

Lepton::Lepton(const TLorentzVector * const lorentz_vector, const TVectorD *const info) :
  PhysicsObject(lorentz_vector, info)
{
}

Lepton::Lepton(const LorentzVector math_lorentz_vector) : PhysicsObject(math_lorentz_vector)
{
}

Lepton::Lepton(const LorentzVectorF math_lorentz_vector_f) : PhysicsObject(math_lorentz_vector_f)
{
}

/*void Lepton::ListLorentzVector() const
{
  
  printf("Pt=% 10f E=% 10f Eta=% 10f Phi=% 10f\n", Pt(), E(), Eta(), Phi());
 
  }*/

void Lepton::ls(const char * option) const
{
}


Lepton::~Lepton()
{
}

const char* Electron::title = "electron";

Electron::Electron() :
  Lepton::Lepton()
{
  ((Lepton*)(this)) -> title = TString(title);
}

Electron::Electron(const TLorentzVector * const lorentz_vector, const TVectorD * const info) :
  Lepton(lorentz_vector, info)
{
  charge = (*info)[(char)ElectronInfo::ID] > 0 ? 1 : -1;
  relative_isolation = (*info)[(char)ElectronInfo::REL_ISOLATION];
  ((Lepton*)(this)) -> title = TString(title);

}

Electron::Electron(const llvvLepton llvvLepton_obj) :
  Lepton(llvvLepton_obj)
{
  charge = (llvvLepton_obj.id > 0) ? 1 : -1;
  ((Lepton*)(this)) -> title = TString(title);

}

void Electron::ls(const char * option) const 
{
  ListLorentzVector();
  if (TString(option) == "verbose")
    {
      printf("      charge %d, rel_isol = %f\n", charge, relative_isolation);       
    }
}

void Electron::ListLorentzVector() const
{
  
  printf("Pt=% 10f E=% 10f Eta=% 10f sceta=% 10f Phi=% 10f\n", Pt(), E(), Eta(), el_info.sceta, Phi());
 
}

/*Electron::~Electron()
{
}*/

const char* Muon::title = "muon";


Muon::Muon() :
  Lepton::Lepton()
{
  ((Lepton*)(this)) -> title = TString(title);

}

Muon::Muon(const TLorentzVector * const lorentz_vector, const TVectorD * const info) :
  Lepton(lorentz_vector, info)
{
  charge = (*info)[(char)MuonInfo::ID] > 0 ? 1 : -1;
  relative_isolation = (*info)[(char)MuonInfo::REL_ISOLATION];
  ((Lepton*)(this)) -> title = TString(title);

}

Muon::Muon(const llvvLepton llvvLepton_obj) :
  Lepton(llvvLepton_obj)
{
  charge = (llvvLepton_obj.id > 0) ? 1 : -1;
  ((Lepton*)(this)) -> title = TString(title);

}

void Muon::ls(const char * option) const 
{
  ListLorentzVector();
  if (TString(option) == "verbose")
    {
      printf("      charge %d, rel_isol = %f\n", charge, relative_isolation);       
    }
}


/*Muon::~Muon()
{
}*/

const char* Tau::title = "tau";


Tau::Tau() : 
  Lepton()
{
  ((Lepton*)(this)) -> title = TString(title);

}

Tau::Tau(const TLorentzVector * const lorentz_vector, const TVectorD * const info) :
    Lepton(lorentz_vector, info)
{
  charge = (*info)[(char)TauInfo::ID] > 0 ? 1 : -1;
  ((Lepton*)(this)) -> title = TString(title);

}

Tau::Tau(const llvvTau llvvTau_obj) :
  Lepton(llvvTau_obj)
{
  charge = (llvvTau_obj.id > 0) ? 1 : -1;
  ((Lepton*)(this)) -> title = TString(title);

}

void Tau::ls_tracks() const 
{
  printf("Listing tau tracks\n");
  if (tracks.size() == 0)
    {
      printf("no tracks\n");
    }
  else
  for (unsigned int ind = 0; ind < tracks.size(); ind ++)
    {
      printf("track ind %u %f\n", ind, tracks[ind].Pt());
    }
}

void Tau::ls(const char * option) const 
{
  ListLorentzVector();
  if (TString(option) == "verbose")
    {
      printf("      charge %d\n", charge);       
    }
}

bool Tau::passID(const uint64_t IdBit) const
{
  return (idbits & ((uint64_t)1<<IdBit)) > 0;
}

/*Tau::~Tau()
{
}*/

Jet::Jet() :
  PhysicsObject()
{
}

Jet::Jet(const TLorentzVector * const lorentz_vector, const TVectorD * const info) :
  PhysicsObject(lorentz_vector, info)
{
  CSV_discriminator = (*info)[(char)JetInfo::BTAG] > 0 ? 1 : -1;
  genJetPt = (*info)[(char)JetInfo::GENJETPT];
  jetpgid = (*info)[(char)JetInfo::JETPGID];
}

Jet::Jet(const llvvJetExt llvvJetExt_obj) :
  PhysicsObject(llvvJetExt_obj)
{
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

void Jet::ls(const char * option) const 
{
  ListLorentzVector();
  if (TString(option) == "verbose")
    {
      printf("      b-tagged = %s\n", BTagSFUtil_isBtagged ? "true" : "false");       
    }
  
}


/*Jet::~Jet()
{
}*/

MET::MET() :
  PhysicsObject()
{
}

MET::MET(const TLorentzVector * const lorentz_vector, const TVectorD * const info) :
    PhysicsObject(lorentz_vector, info)
{
}

MET::MET(const TLorentzVector &tlorentz_vector) : PhysicsObject(tlorentz_vector)
{

}

MET::MET(const llvvMet llvvMet_obj) :
  PhysicsObject(llvvMet_obj)        
{
}


void MET::ls(const char * option) const 
{
  ListLorentzVector();
}


/*MET::~MET()
{
}*/

 /*Vertex::Vertex()
{
}*/

void Vertex::ls(const char * option) const
{
}

/*Vertex::~Vertex()
{
}*/
