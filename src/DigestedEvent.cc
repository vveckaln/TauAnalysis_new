#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
#include "TMath.h"
using namespace cpHistogramPoolRegister;

DigestedEvent::DigestedEvent()
{
  non_const_object = NULL;
}

DigestedEvent::~DigestedEvent()
{
}

void DigestedEvent::Open()
{
  
}

void DigestedEvent::Close()
{
  
}

Jet *DigestedEvent::GetLeadingJet(const char* field, const int rank) const 
{
  double (DigestedEvent::*func)(const uint) const ;
  if (TString(field) == "Pt")   func = &DigestedEvent::GetJetPt;
  if (TString(field) == "Btag") func = &DigestedEvent::GetJetBtag;
   
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

unsigned char DigestedEvent::GetBtagCount() const
{
  unsigned char BtagCount = 0;
  for (unsigned short ind = 0; ind < Jets.size(); ind ++)
    {
   
      if (Jets[ind].BTagSFUtil_isBtagged) BtagCount ++;
    }
  return BtagCount;
}

double DigestedEvent::GetJetPt(const uint index) const
{
  return Jets[index].GetPt();
}
Object * DigestedEvent::GetObject(const char * type, const uint ind) 
{
  if (TString(type) != "vertex")
    {
      if (non_const_object)
	{
	  TLorentzVector difference = *non_const_object - previous_state;
	  met[0] -= difference;
	}
    }  
  if (TString(type) == "electron")
    {
      previous_state = Electrons.at(ind);
      non_const_object = &Electrons.at(ind);
      return &Electrons.at(ind);
    }
  if (TString(type) == "muon")
    {
      previous_state = Muons.at(ind);
      non_const_object = &Muons.at(ind);
      return &Muons.at(ind);
    }
  if (TString(type) == "tau")
    {
      previous_state = Taus.at(ind);
      non_const_object = &Taus.at(ind);
      return &Taus.at(ind);
    }
  if (TString(type) == "jet")
    {
      previous_state = Jets.at(ind);
      non_const_object = &Jets.at(ind);
      return &Jets.at(ind);
    }
  if (TString(type) == "MET")
    {
      previous_state = met.at(ind);
      non_const_object = &met.at(ind);
      return &met.at(ind);
    }
  if (TString(type) == "vertex")   return &Vertices.at(ind);
  return NULL;
}

PhysicsObject * DigestedEvent::GetPhysicsObject(const char * type, const uint ind) 
{
  if (TString(type) == "vertex") return NULL;
  return (PhysicsObject*) GetObject(type, ind);
}

const Object * DigestedEvent::GetConstObject(const char * type, const uint ind) const
{
  if (TString(type) == "electron") return &Electrons.at(ind);
  if (TString(type) == "muon")     return &Muons.at(ind);
  if (TString(type) == "tau")      return &Taus.at(ind);
  if (TString(type) == "jet")      return &Jets.at(ind);
  if (TString(type) == "MET")      return &met.at(ind);
  if (TString(type) == "vertex")   return &Vertices.at(ind);
  return NULL;
}

const PhysicsObject * DigestedEvent::GetConstPhysicsObject(const char * type, const uint ind) const
{
  if (TString(type) == "vertex") return NULL;
  return (PhysicsObject*) GetConstObject(type, ind);
}

unsigned char DigestedEvent::GetObjectCount(const char * type) const
{
  if (TString(type) == "electron") return Electrons.size();
  if (TString(type) == "muon")     return Muons.size();
  if (TString(type) == "tau")      return Taus.size();
  if (TString(type) == "jet")      return Jets.size();
  if (TString(type) == "met")      return met.size();
  if (TString(type) == "vertex")   return Vertices.size();
  return 0;
}

Lepton * DigestedEvent::GetLeadingLepton(const char * option) const
{
  double Pt = -1;
  if (TString(option) == "electron" or TString(option) == "muon")
    {
      const Lepton * lepton = NULL; 
      for (unsigned char ind = 0; ind < GetObjectCount(option); ind ++)
	{
	  if (GetConstPhysicsObject(option, ind) -> Pt() > Pt)
	    {
	      lepton = (Lepton*)GetConstObject(option, ind);
	      Pt = lepton -> Pt();
	    }
	}
      return const_cast<Lepton*>(lepton);
    }

  if (TString(option) == "electronmuon" )
    {
      const Lepton * const electron = (Lepton*) GetLeadingLepton("electron");
      const Lepton * const muon = (Lepton*) GetLeadingLepton("muon");
      if (electron == NULL) return const_cast<Lepton*>(muon);
      if (muon == NULL) return const_cast<Lepton*>(electron);
      return electron -> Pt() > muon -> Pt() ? 
	const_cast<Lepton*>(electron) : 
	const_cast<Lepton*>(muon);
    }
  return NULL;
}

void DigestedEvent::erase(const char *field, const uint ind)
{
  if (TString(field) == "electron") Electrons.erase(Electrons.begin() + ind);
  if (TString(field) == "muon")     Muons.erase(Muons.begin() + ind);
  if (TString(field) == "tau")      Taus.erase(Taus.begin() + ind);
  if (TString(field) == "jet")      Jets.erase(Jets.begin() + ind);
  if (TString(field) == "MET")      met.erase(met.begin() + ind);
  if (TString(field) == "vertex")   Vertices.erase(Vertices.begin() + ind);

}

unsigned char DigestedEvent::PurgeIsNaN()
{
  unsigned char purges = 0;
  const char numb_fields = 5;
  const char *fields[numb_fields] = 
    {"electron", "muon", "tau", "jet", "met"};
    for (ushort field_ind = 0; field_ind < numb_fields; field_ind ++)
    {
      for (unsigned char ind = 0; ind < GetObjectCount(fields[field_ind]); ind ++)
      {
        const PhysicsObject * const po = (PhysicsObject*) GetObject(fields[field_ind], ind);
	if (std::isnan(po -> Px()) or std::isnan(po -> Py()) or 
	    std::isnan(po -> Pz()) or std::isnan(po -> E()))
	{
	  erase(fields[field_ind], ind);
	  purges ++;
	}
      }
    }
    return purges;
}

unsigned char DigestedEvent::PurgeZeroPt()
{
  unsigned char purges = 0;
  const char numb_fields = 5;
  const char *fields[numb_fields] = 
    {"electron", "muon", "tau", "jet", "met"};
    for (ushort field_ind = 0; field_ind < numb_fields; field_ind ++)
    {
      for (unsigned char ind = 0; ind < GetObjectCount(fields[field_ind]); ind ++)
      {
        const PhysicsObject * const po = (PhysicsObject*) GetObject(fields[field_ind], ind);
	
	if (po -> Pt() < 1E-3)
	{
	  erase(fields[field_ind], ind);
	  purges ++;
	}
      }
    }
    return purges;
}

void DigestedEvent::ls(const char* field, const char *option) const 
{
  if (TString(field) == "all")
    {
      const char numb_fields = 5;
      const char *fields[numb_fields] = 
	{"electron", "muon", "tau", "jet", "met"};
      for (ushort field_ind = 0; field_ind < numb_fields; field_ind ++)
	{
	  ls(fields[field_ind]);
	}
      return;
    }
  printf("Listing field %s\n", field);
  if (GetObjectCount(field) == 0) 
    {
      printf("   No objects\n");
    }
  for (unsigned char ind = 0; ind < GetObjectCount(field); ind ++)
    {
      printf("   Object %2u : ", ind);
      GetConstObject(field, ind) -> ls(option);
    }
  
}

void DigestedEvent::ApplyJetEnergyScale(const uint uncertainty_subsignal) const{
  /* for (ushort jet_ind = 0; jet_ind < Jets.size(); jet_ind++){
    const PhysicsObject * const jet = &Jets [jet_ind];
    //if (uncertainty_signal != JES) return jet -> Pt();

    const double Pt  = jet -> Pt();
    const double Eta = jet -> Eta();

    jetCorrectionUncertainty -> setJetEta(Eta);
    jetCorrectionUncertainty -> setJetPt(Pt); 
    float correction = jetCorrectionUncertainty -> getUncertainty(true);
    if (uncertainty_subsignal == MINUS) correction *= -1;
    }*/
}

void DigestedEvent::SmearJets(){
  /* //Reference "Jet Energy Resolution", CMS Workbook twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution, retrieved on October 30, 2014
  const ushort number_bins = 5;
  const float bin_boundaries[number_bins][2] = 
    {{0.0, 0.5}, 
     {0.5, 1.1},
     {1.1, 1.7},
     {1.7, 2.3},
     {2.3, 5.0}};
  const float factor[number_bins] = 
    {1.052, 1.057, 1.096, 1.134, 1.288};
  const float statistical_error[number_bins] =
    {0.012, 0.012, 0.017, 0.035, 0.127};
  const float systematic_error_plus[number_bins] =
    {0.062, 0.056, 0.063, 0.087, 0.155};  
  const float systematic_error_minus[number_bins] =
    {0.061, 0.055, 0.062, 0.085, 0.153};    
  
  for (ushort jet_ind = 0; jet_ind < Jets.size(); jet_ind ++)
  {
    
    const double AbsEta = fabs(Jets[jet_ind] . Eta());
    const double Pt = Jets[jet_ind].Pt();
    float ptSF = 1.0;
    double ptSF_err = 0.06;
    const double genJetPt = Jets[jet_ind] . genJetPt;
    for (ushort ind = 0; ind < number_bins; ind++){
      if (AbsEta <= bin_boundaries[ind][0] and 
	  AbsEta < bin_boundaries[ind][1]){
	ptSF = factor[ind];
	ptSF_err = sqrt(pow(statistical_error[ind], 2) +
			pow((systematic_error_plus[ind] + 
			     systematic_error_minus[ind])/2, 2));
	break;
      }
    }
    if (uncertainty_signal == JER){
      if (uncertainty_subsignal == PLUS) ptSF += ptSF_err;
      else if (uncertainty_subsignal == MINUS) ptSF -= ptSF_err;
    }
    ptSF = max(0.0, (genJetPt + ptSF*(Pt - genJetPt)))/Pt;
    if (ptSF == 0) printf("%s %s %s PtSF = 0\n", (uncertainties_activated) ? "true" : "false", uncertainty_name[uncertainty_signal], uncertainty_subname[uncertainty_subsignal]);
    const double 
      Px(Jets[jet_ind].Px()*ptSF),
      Py(Jets[jet_ind].Py()*ptSF),
      Pz(Jets[jet_ind].Pz()*ptSF),
      mass(Jets[jet_ind].M());
    const double En = sqrt(pow(mass, 2) + 
			   pow(Px, 2) + 
			   pow(Py, 2) + 
			   pow(Pz,2));
    const TLorentzVector old_jet = (TLorentzVector) Jets[jet_ind];
    Jets[jet_ind] . SetPxPyPzE(Px, Py, Pz, En);
    jet_difference += Jets[jet_ind] - old_jet;
    }*/

}

void DigestedEvent::CorrectMET() 
{
  if (non_const_object)
    {
      TLorentzVector jet_difference = *non_const_object - previous_state;
      met[0] -= jet_difference;
      non_const_object = NULL;
    }
}

void DigestedEvent::Print4VectorSum() const
{
  TLorentzVector sum4vector; 
  for (ushort muon_ind = 0; muon_ind < Muons.size(); muon_ind ++){
    sum4vector += (TLorentzVector) Muons[muon_ind];
  }
  for (ushort electron_ind = 0; electron_ind < Electrons.size(); electron_ind ++){
    sum4vector += (TLorentzVector) Electrons[electron_ind];
  }
  for (ushort tau_ind = 0; tau_ind < Taus.size(); tau_ind ++){
    sum4vector += (TLorentzVector) Taus[tau_ind];
  }
  for (ushort jet_ind = 0; jet_ind < Jets.size(); jet_ind ++){
    sum4vector += (TLorentzVector) Jets[jet_ind];
  }
  sum4vector += (TLorentzVector) met[0];
  printf("Px %f  Py %f  Pz %f E %f\n", sum4vector.Px(), sum4vector.Py(), sum4vector.Pz(), sum4vector.E());
 
  getchar();
}
