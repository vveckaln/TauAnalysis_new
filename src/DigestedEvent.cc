#include "LIP/TauAnalysis/interface/DigestedEvent.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"

#include "TMath.h"
using namespace cpregister;
using namespace gVariables;

DigestedEvent::DigestedEvent()
{
  non_const_object = NULL;
  print_mode = false;
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
  if (TString(type) == "all") return GetObjectCount("electron") + GetObjectCount("muon") + 
				GetObjectCount("tau") + GetObjectCount("jet") + GetObjectCount("met") 
				+ GetObjectCount("vertex");
  return 0;
}

bool DigestedEvent::ValidateElectron(const unsigned short electron_ind) const
{
  double const ref_rel_isolation            = 0.15;

  const GeV    ELECTRON_PT_MIN              = 35;
  const double ELECTRON_ETA_MAX             = 2.5;
  const double ETA_EXCLUSION_REGION_MIN     = 1.4442;
  const double ETA_EXCLUSION_REGION_MAX     = 1.5660;
  const Electron * const electron           = &Electrons[electron_ind];
  const double relative_isolation           = electron -> relative_isolation;
  const double AbsEta                       = fabs(electron -> el_info.sceta);
  const GeV    Pt                           = electron -> Pt();
  const bool   relative_isolation_valid     = relative_isolation < ref_rel_isolation;
  const bool   Eta_valid                    = AbsEta < ELECTRON_ETA_MAX;
  const bool   Pt_valid                     = Pt > ELECTRON_PT_MIN;
  const bool   dZ_valid                     = fabs(electron -> dZ) < 1;
  const bool   d0_valid                     = electron -> d0 < 0.02;
  const bool   outside_eta_exclusion_region = AbsEta < ETA_EXCLUSION_REGION_MIN or AbsEta > ETA_EXCLUSION_REGION_MAX;
  
  bool         passID                       = true;
  if (electron -> el_info.isConv) passID = false;
  const float MVATriggerV0(electron -> el_info.mvatrigv0);
  if (AbsEta < 0.8 and MVATriggerV0 < 0.94)
      passID = false;
  if (AbsEta < 1.479 and AbsEta > 0.8 and MVATriggerV0 < 0.85) 
      passID = false;
  if (AbsEta > 1.479 and MVATriggerV0 < 0.92)
      passID = false;
  
  const bool electron_valid = Eta_valid and Pt_valid and outside_eta_exclusion_region and passID and relative_isolation_valid and dZ_valid and d0_valid;
  //electron -> ls("verbose");
  
  /*printf("Eta valid = %s, Pt valid %s, IsConv = %s, MVATriggerV0 = %f, relative_isolation_valid = %s\n",
      Eta_valid                ? "true" : "false",
      Pt_valid                 ? "true" : "false",
      electron -> el_info.isConv ? "true" : "false",
      electron -> el_info.mvatrigv0,
	     
      relative_isolation_valid ? "true" : "false");
      printf("Electron valid VALID = %s\n", electron_valid ? "true" : "false");*/
  return electron_valid;

}

bool DigestedEvent::ValidateMuon(const unsigned short muon_ind) const
{
  double const ref_rel_isolation        = 0.12; 
  const GeV    MUON_PT_MIN              = 30;
  const double MUON_ETA_MAX             = 2.1;
  const Muon * const muon               = &Muons[muon_ind];
  const double relative_isolation       = muon -> relative_isolation;
  const double AbsEta                   = fabs(muon -> Eta());
  const GeV    Pt                       = muon -> Pt();
  const bool   relative_isolation_valid = relative_isolation < ref_rel_isolation;
  const bool   Eta_valid                = AbsEta < MUON_ETA_MAX;
  const bool   Pt_valid                 = Pt > MUON_PT_MIN;
  const bool   dZ_valid                 = muon -> dZ < 0.5;
  const bool   d0_valid                 = muon -> d0 < 0.2;
  bool         passID                   = true;;
  bool isTight ((muon -> idbits >> 10) & 0x1);
  if(!isTight) passID = false;

  const bool muon_valid = Eta_valid and Pt_valid and passID and relative_isolation_valid and dZ_valid and d0_valid;
  /*if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("LEADING LEPTON VALIDATION:\n");
      printf("Eta valid = %s, Pt valid %s, passID valid = %s, relative_isolation_valid = %s\n",
      Eta_valid                ? "true" : "false",
      Pt_valid                 ? "true" : "false",
      passID                   ? "true" : "false",
      relative_isolation_valid ? "true" : "false");
      printf("LEADING LEPTON VALID = %s\n", muon_valid ? "true" : "false");
      }*/
  return muon_valid;
}


Lepton * DigestedEvent::GetLeadingLepton(const char * option) const
{
 
  double Pt = -1;
  if (TString(option) == "electron" or TString(option) == "muon")
    {
      const Lepton * lepton = NULL; 
      for (unsigned char ind = 0; ind < GetObjectCount(option); ind ++)
	{
	  const bool lepton_valid = (TString(option) == "electron") ? ValidateElectron(ind) : ValidateMuon(ind);
	  if (lepton_valid and GetConstPhysicsObject(option, ind) -> Pt() > Pt)
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
      const Lepton * const muon     = (Lepton*) GetLeadingLepton("muon");
      if (electron == NULL) return const_cast<Lepton*>(muon);
      if (muon     == NULL) return const_cast<Lepton*>(electron);
      return electron -> Pt() > muon -> Pt() ? 
	const_cast<Lepton*>(electron) : 
	const_cast<Lepton*>(muon);
    }
  return NULL;
}

bool DigestedEvent::ValidateJet(const unsigned short jet_ind, const Lepton & lepton) const
{
  const GeV JET_PT_MIN            = 20;
  const double JET_ETA_MAX        = 2.4;
  const double JET_LEPTON_DR_MIN  = 0.3;//0.4;
    
  const Jet * const jet           = &Jets . at(jet_ind);
  const double DeltaR             = jet -> DeltaR(lepton);
  const double Pt                 = jet -> /*GetPt()*/ Pt();
  const double AbsEta             = fabs(jet -> Eta());
  if (Pt < 15 or AbsEta > 4.7) return false; 
  const bool DeltaR_valid         = DeltaR > JET_LEPTON_DR_MIN;
  const bool Eta_valid            = AbsEta < JET_ETA_MAX;
  const bool Pt_valid             = Pt > JET_PT_MIN;
  const bool passPFloose          = (jet -> idbits >> 0) & 0x1;
  const int  puId                 = (jet -> idbits >> 3) & 0xf;
  const bool passLoosePuId        = (puId >> 2) & 0x1;
  const bool Jet_valid            = DeltaR_valid 
    and Eta_valid 
    and Pt_valid
    and passPFloose
      and passLoosePuId;
  //printf("DeltaR %f PT %f passPFloose %s passLoosePuId %s\n", DeltaR, jet -> Pt(), passPFloose ? "true" : "false", passLoosePuId ? "true" : "false");
  return Jet_valid;
}

bool DigestedEvent::ValidateTau(const unsigned short tau_ind, const Lepton * lepton) const
{
  const GeV TAU_PT_MIN       = 20; 
  const double TAU_ETA_MAX   = 2.4;
  
  const Tau * const tau                = &Taus.at(tau_ind); 
  const double AbsEta                  = fabs(tau -> Eta());
  const double tau_Pt                  = tau -> Pt();
  if(tau_Pt < 20.0 || AbsEta > 2.3) return false;
  const bool tau_Eta_valid             = AbsEta < TAU_ETA_MAX;
  const bool tau_Pt_valid              = tau_Pt > TAU_PT_MIN;
  const bool againstElectronMediumMVA5 = tau -> passID(llvvTAUID::againstElectronMediumMVA5);
  const bool againstMuonTight2         = tau -> passID(llvvTAUID::againstMuonTight2);
  const bool decayModeFinding          = tau -> passID(llvvTAUID::decayModeFinding);
  const bool byMediumCombinedIsolationDeltaBetaCorr3Hits = tau -> passID(llvvTAUID::byMediumCombinedIsolationDeltaBetaCorr3Hits);
  const bool passID                    = againstElectronMediumMVA5
    and againstMuonTight2 
    and decayModeFinding 
    and byMediumCombinedIsolationDeltaBetaCorr3Hits;
      
  double tau_lepton_deltaR;
  bool overlapwithlepton;
  if (lepton)
    {
     tau_lepton_deltaR = tau -> DeltaR(*lepton);
     overlapwithlepton = tau_lepton_deltaR < 0.1;
    }
  else overlapwithlepton = false;
  const bool dZvalid                   = abs(tau -> dZ) < 0.5; 
  const bool emfraction_valid          = tau -> emfraction < 2;
  const bool tau_valid                 = tau_Eta_valid 
    and tau_Pt_valid 
    and passID 
    and tau -> isPF 
    and dZvalid 
    and emfraction_valid 
    and not overlapwithlepton;
      
    if (print_mode)
      {
	  printf("listing Tau\n");
	  tau -> ls("verbose");
	  printf("tau.idbits %lu\n", tau -> idbits);// cout<<tau -> idbit<<;
	  
	  //cout<<"test "<< tau-> idbits & ((uint64_t)1<<llvvTAUID::againstMuonTight2);
	  printf("\nEta valid = %s, Pt valid = %s, \n overlapwithlepton %s againstElectronMediumMVA5 = %s, againstMuonTight2 = %s, decayModeFinding = %s, byMediumCombinedIsolationDeltaBetaCorr3Hits = %s\n isPF %s, dZ %f, emfraction %f", 
		 tau_Eta_valid                    ? "true" : "false", 
		 tau_Pt_valid                     ? "true" : "false", 
		 overlapwithlepton                ? "true" : "false",
		 againstElectronMediumMVA5        ? "true" : "false",
		 againstMuonTight2                ? "true" : "false",
		 decayModeFinding                 ? "true" : "false",
		 byMediumCombinedIsolationDeltaBetaCorr3Hits
		 ? "true" : "false",		 
		 tau -> isPF                      ? "true" : "false",
		 abs(tau -> dZ), tau -> emfraction);
	  printf("Tau valid = %s\n", tau_valid ? "true" : "false");
   }
 return tau_valid; 
}

bool DigestedEvent::DeleteTauJet(const Lepton * const lepton)
{
  const double ref_DeltaR = 0.4;
  bool TauJetFound = false;
  for (ushort jet_ind = 0; jet_ind < Jets.size(); jet_ind ++)
  {
    //if (not ValidateJet(jet_ind, *lepton)) continue;
    const Jet* const jet = &Jets[jet_ind];
    for (unsigned short tau_ind = 0; tau_ind < Taus.size(); tau_ind ++)
      {
	const Tau* const tau = &Taus[tau_ind];
	const double DeltaR = jet -> DeltaR(*tau);
	if (DeltaR < ref_DeltaR) 
	  {
	    /*printf("jet\n");
	    Jets[jet_ind].ls("verbose");
	    printf("tau\n");
	    Taus[tau_ind].ls("verbose");*/
	    Jets.erase(Jets.begin() + jet_ind);
	    TauJetFound = true;      
	  }
      }
  }
  //getchar();

  return TauJetFound;
}

unsigned short DigestedEvent::GetBtagCount(const Lepton & lepton) const
{
  unsigned char Btag_count = 0;
  for (uint jet_ind = 0; jet_ind < Jets . size(); jet_ind ++)  
    {
      const bool jet_valid = ValidateJet(jet_ind, lepton) and Jets[jet_ind].Pt() > 30;

      // printf("Counting jet %u, jet valid %s, btagged %s\n", jet_ind, jet_valid ? "true": "false", Jets[jet_ind].BTagSFUtil_isBtagged ? "true" : "false");
      
      if (jet_valid)
	if (Jets[jet_ind].BTagSFUtil_isBtagged) Btag_count ++;
    }
  return Btag_count;
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
	  ls(fields[field_ind], option);
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
