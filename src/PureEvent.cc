#include "LIP/TauAnalysis/interface/PureEvent.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
using namespace cpHistogramPoolRegister;

PureEvent::PureEvent()
{
  
}

PureEvent::~PureEvent()
{
  Jets.clear();
  Vertices.clear();
}

void PureEvent::Open()
{
  
}

void PureEvent::Close()
{
  
}

Jet *PureEvent::GetLeadingJet(const char* field, const int rank) const 
{
  double (PureEvent::*func)(const uint) const ;
  if (TString(field) == "Pt")   func = &PureEvent::GetJetPt;
  if (TString(field) == "Btag") func = &PureEvent::GetJetBtag;
   
  Jet const *leading_jet[rank];
  for (unsigned char ind = 0; ind < rank; ind ++){
    double previous_value = -100;
    
    for (unsigned int jet_ind = 0; jet_ind < Jets.size(); jet_ind ++){
      const Jet * const jet = &Jets[jet_ind];
      if ((this->*func)(jet_ind) > previous_value){
	bool identified = false;
	for (unsigned char ind2 = 0; ind2 < ind; ind2 ++){
	  if (jet == leading_jet[ind2]) identified = true;
	  
	}
	if (not identified){ 
	  leading_jet[ind] = jet;
	  previous_value = (this ->* func)(jet_ind);
	}
      }
    }
  }
  
  return const_cast<Jet*>(leading_jet[rank - 1]);
}

unsigned char PureEvent::GetBtagCount() const
{
  unsigned char BtagCount = 0;
  const double BTAG_CUT             = 0.679;
  for (unsigned short ind = 0; ind < Jets.size(); ind ++){
    if (Jets[ind].CSV_discriminator > BTAG_CUT) BtagCount ++; 
  }
  return BtagCount;
}

double PureEvent::GetJetPt(const uint index) const{
  /* const Jet * jet = &Jets[index];
  if (uncertainty_signal != JES) return jet -> Pt();

  const double Pt  = jet -> Pt();
  const double Eta = jet -> Eta();

  jetCorrectionUncertainty -> setJetEta(Eta);
  jetCorrectionUncertainty -> setJetPt(Pt); 
  float correction = jetCorrectionUncertainty -> getUncertainty(true);
  if (uncertainty_subsignal == MINUS) correction *= -1;
  return (1 + correction)*Pt;*/
  return -1;

}

/*Lepton * PureEvent::GetLeadingLepton() const{
  
  }*/

void PureEvent::ls(const char* field) const {
  const vector<PhysicsObject> * vect;
  if (TString(field) == "jet") vect = (const vector<PhysicsObject>*) &Jets;
  else vect = NULL;
  for (unsigned char ind = 0; ind < vect -> size(); ind ++){
    printf("Object %u\n", ind);
    vect -> at(ind) . ListLorentzVector();
    printf("Btag = %f\n", ((const vector<Jet> *)vect) -> at(ind) . CSV_discriminator);
  }
}

void PureEvent::Print4VectorSum() const
{
  TLorentzVector sum4vector; 
  
  getchar();
}
