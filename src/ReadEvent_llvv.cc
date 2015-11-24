#include "TauAnalysis/interface/ReadEvent_llvv.hh"


ReadEvent_llvv::ReadEvent_llvv()
{
}

void ReadEvent_llvv::Open()
{
}

void ReadEvent_llvv::Close()
{
  /*leptons.~vector<llvvLepton>();//clear();
  taus.~vector<llvvTau>();//clear();
  jets.~vector<llvvJetExt>(); //clear();
  */
}

const reco::LeafCandidate * ReadEvent_llvv::GetConstObject(const char * type, const uint ind) const
{
  const TString type_str(type);
  if (type_str == "electron") return &electrons.at(ind);
  if (type_str == "muon")     return &muons.at(ind);
  if (type_str == "tau")      return &taus.at(ind);
  if (type_str == "jet")      return &jets.at(ind);
  if (type_str == "MET")      return &MET.at(ind);
  return NULL;
}

reco::LeafCandidate * ReadEvent_llvv::GetLeadingLepton(const char * option) const
{
 
  double Pt = -1;
  if (TString(option) == "electron" or TString(option) == "muon")
    {
      const reco::LeafCandidate * lepton = NULL; 
      for (unsigned char ind = 0; ind < GetObjectCount(option); ind ++)
	{
	  //const bool lepton_valid = (TString(option) == "electron") ? ValidateElectron(ind) : ValidateMuon(ind);
	  if (GetConstObject(option, ind) -> pt() > Pt)
	    {
	      lepton = (reco::LeafCandidate*)GetConstObject(option, ind);
	      Pt = lepton -> pt();
	    }
	}
      return const_cast<reco::LeafCandidate*>(lepton);
    }

  if (TString(option) == "electronmuon" )
    {
      const reco::LeafCandidate * const electron = (reco::LeafCandidate*) GetLeadingLepton("electron");
      const reco::LeafCandidate * const muon     = (reco::LeafCandidate*) GetLeadingLepton("muon");
      if (electron == NULL) return const_cast<reco::LeafCandidate*>(muon);
      if (muon     == NULL) return const_cast<reco::LeafCandidate*>(electron);
      return electron -> pt() > muon -> pt() ? 
	const_cast<reco::LeafCandidate*>(electron) : 
	const_cast<reco::LeafCandidate*>(muon);
    }
  return NULL;
}

unsigned char ReadEvent_llvv::GetObjectCount(const char * type) const
{
  const TString type_str(type);
  if (type_str == "electron") return electrons.size();
  if (type_str == "muon")     return muons.size();
  if (type_str == "tau")      return taus.size();
  if (type_str == "jet")      return jets.size();
  if (type_str == "met")      return MET.size();
  if (type_str == "all") return GetObjectCount("electron") + GetObjectCount("muon") + 
				GetObjectCount("tau") + GetObjectCount("jet") + GetObjectCount("met");
  return 0;
}

reco::LeafCandidate * ReadEvent_llvv::GetObject(const char * type, const uint ind) 
{
  const TString type_str(type);
  if (non_const_object)
    {
      const LorentzVector difference = *non_const_object - previous_state;
      const LorentzVector met_p4 = MET[0].p4();
      MET[0].setP4(met_p4 - difference);
    }
 
  if (type_str == "electron")
    {
      previous_state = electrons[ind].p4();
      non_const_object = &electrons[ind].p4();
      return &electrons[ind];
    }
  if (type_str == "muon")
    {
      previous_state = muons[ind].p4();
      non_const_object = &muons[ind].p4();
      return &muons[ind];
    }
  if (type_str == "tau")
    {
      previous_state = taus[ind].p4();
      non_const_object = &taus[ind].p4();
      return &taus[ind];
    }
  if (type_str == "jet")
    {
      previous_state = jets[ind].p4();
      non_const_object = &jets[ind].p4();
      return &jets[ind];
    }
  if (type_str == "MET")
    {
      previous_state = MET[ind].p4();
      non_const_object = &MET[ind].p4();
      return &MET[ind];
    }
  return NULL;
}

void ReadEvent_llvv::CorrectMET() 
{
  if (non_const_object)
    {
      LorentzVector jet_difference = *non_const_object - previous_state;
      MET[0].setP4(MET[0].p4() - jet_difference);
      non_const_object = NULL;
    }
}


ReadEvent_llvv::~ReadEvent_llvv()
{
}

