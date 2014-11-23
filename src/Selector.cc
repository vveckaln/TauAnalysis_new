#include "LIP/TauAnalysis/interface/Selector.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/Parser.hh"

#include <math.h>

Selector::Selector(EventSink<PureEvent *> *next_processor_stage):EventProcessor<DigestedEvent*, PureEvent *>(next_processor_stage)
{
  mapOfSelectorHistoPools = new MapOfObjectPools<TH1D>();

  HistogramPool * base_pool = new HistogramPool(selector_h_descriptors, "SELECTOR_BASE");
  base_pool -> SetDirectoryName("SELECTOR_BASE");
  mapOfSelectorHistoPools -> Add((ObjectPool<TH1D>*)base_pool);
  base_pool -> at("numb_events_selection_stages") -> SetBit(TH1::kCanRebin);

  if (not gnoUncertainties)
  {
    for (ushort ind = 0; ind < number_uncertainties; ind ++)
    {
      for (ushort subind = 0; subind < number_subuncertainties; subind ++) 
      {
	const TString title = "SELECTOR_" + TString(uncertainty_name[ind]) + "_" + 
			      TString(uncertainty_subname[subind]);
	HistogramPool *pool = new HistogramPool(selector_h_descriptors, 
						title);
	pool -> SetDirectoryName(title);
	mapOfSelectorHistoPools -> Add((ObjectPool<TH1D>*)pool); 
        pool -> at("numb_events_selection_stages") -> SetBit(TH1::kCanRebin);
      }	
    }
  }
}

void Selector::Run()
{
  output_buffer = new EventBuffer<PureEvent*>(10);
  for (unsigned char ind = 0; ind < input_buffer -> size(); ind ++)
    { 
      processed_event = (*input_buffer)[ind];
      
      ChannelGate();
     
      if (not CheckTrigger()) continue;
      if (IsLowQualityEvent()) continue;
      lepton = NULL;
      if (ValidateEvent()) 
	{
	  //DeleteHadronisedTauJet();
	  //FinishPureEvent();
	  *output_buffer -> GetWriteSlot() = pure_event;
      
	  output_buffer -> PushWriteSlot();
	}
      if (output_buffer -> IsFull())
	{
	  ProceedToNextStage();
	  delete output_buffer;
	  output_buffer = new EventBuffer<PureEvent*>(10);
	}
    }
  if (!output_buffer -> IsEmpty())
    {
      ProceedToNextStage();
      delete output_buffer;
     }
}

void Selector::ChannelGate() const
{
  const Lepton * const lepton = processed_event -> GetLeadingLepton("electronmuon");
  if (lepton == NULL) return;
  if (lepton -> title == "muon") geChONmuChOFF = false;
  if (lepton -> title == "electron") geChONmuChOFF = true;
}

bool Selector::CheckTrigger() const
{
  if (not geChONmuChOFF)
    {
      const bool muon_trigger(processed_event -> triggerBits[6]);
      if (muon_trigger) return true;
    }
  return false;
}

bool Selector::IsLowQualityEvent() const
{
  if (processed_event -> Electrons.size() == 0 && processed_event -> Muons.size() == 0) return true;
  return false;
}

void Selector::SelectorStatistics(){
  const short size = 6;
  static const char *Selector_report_Xaxis_labels[size] = {
                             "received", 
                             "1 lept + #geq jets", 
                             "E^{miss}_{T}", 
			     "#geq 1btag", 
			     "1#tau", 
			     "OS"
                             };
  
  const TString title = (uncertainties_activated) ? 
    "SELECTOR_" + TString(uncertainty_name[uncertainty_signal]) + "_" + 
    TString(uncertainty_subname[uncertainty_subsignal]) : "SELECTOR_BASE";
  TH1D *h = mapOfSelectorHistoPools -> GetObjectPool(title) 
    -> at("numb_events_selection_stages");
  h -> Fill(Selector_report_Xaxis_labels[0], 1);
  if (LeptonValid && LooseLeptonValid && JetValid) 
    h -> Fill(Selector_report_Xaxis_labels[1], 1);
  else return;
  if (METValid) 
    h -> Fill(Selector_report_Xaxis_labels[2], 1);
  else return;
  if (BtagValid)
    h -> Fill(Selector_report_Xaxis_labels[3], 1);
  if (TausValid)
    h -> Fill(Selector_report_Xaxis_labels[4], 1);
  else return;
  if (TauOS)
    h -> Fill(Selector_report_Xaxis_labels[5], 1);
  else return; 
}

void Selector::Report()
{
  printf("Selector report SELECTOR_BASE\n");
  TH1D *h = mapOfSelectorHistoPools -> GetObjectPool("SELECTOR_BASE") 
    -> at("numb_events_selection_stages");
  h -> LabelsDeflate();
  for (ushort bin_ind = 1; bin_ind <= h -> GetNbinsX(); bin_ind++)
  {
    printf("%u, %u\n", bin_ind, (int)h -> GetBinContent(bin_ind));
  }
  if (not gnoUncertainties){
    for (ushort ind = 0; ind < number_uncertainties; ind ++){
      for (ushort subind = 0; subind < number_subuncertainties; subind ++){
	const TString title = "SELECTOR_" + TString(uncertainty_name[ind]) + "_" + 
			      TString(uncertainty_subname[subind]);
	printf("Selector report %s\n", title.Data());
	TH1D *h = mapOfSelectorHistoPools -> 
	  GetObjectPool("SELECTOR_BASE") 
	  -> at("numb_events_selection_stages");
        h -> LabelsDeflate();
	for (ushort bin_ind = 1; bin_ind <= h -> GetNbinsX(); bin_ind++)
	{
	  printf("%u, %u\n", bin_ind, (int)h -> GetBinContent(bin_ind));
	}
      }	
    }
  }
  ContinueReportToNextStage();

}

bool Selector::ValidateElectron() const
{
  const GeV ELECTRON_PT_MIN             = 35;
  const double ELECTRON_ETA_MAX         = 2.5;
  const double ETA_EXCLUSION_REGION_MIN = 1.4442;
  const double ETA_EXCLUSION_REGION_MAX = 1.5660;
  Electron * const electron = (Electron*)processed_event -> GetLeadingLepton("electron");
  if (electron == NULL) return false;
  const double AbsEta     = fabs(electron -> Eta());
  const GeV  Pt           = electron -> Pt();
  const bool Eta_valid    = AbsEta < ELECTRON_ETA_MAX;
  const bool Pt_valid     = Pt > ELECTRON_PT_MIN;
  const bool outside_eta_exclusion_region = AbsEta < ETA_EXCLUSION_REGION_MIN or AbsEta > ETA_EXCLUSION_REGION_MAX;
  const bool electron_valid   = Eta_valid and Pt_valid and outside_eta_exclusion_region;
  
  if (electron_valid)
    {
      pure_event.lepton = *electron;
      lepton = electron;
    }
  return electron_valid;
}
 
bool Selector::ValidateMuon() const
{
  const GeV MUON_PT_MIN = 30;
  const double MUON_ETA_MAX     = 2.1;
  Muon * const muon = (Muon*)processed_event -> GetLeadingLepton("muon");
  if (muon == NULL) return false;
  const double AbsEta     = fabs(muon -> Eta());
  const GeV  Pt        = muon -> Pt();
  const bool Eta_valid    = AbsEta < MUON_ETA_MAX;
  const bool Pt_valid     = Pt > MUON_PT_MIN;
  const bool muon_valid   = Eta_valid && Pt_valid;
  if (muon_valid)
  {
    pure_event.lepton = (Lepton)*muon;
    lepton = muon;
  }
  return muon_valid;
}

bool Selector::ValidateLooseLepton() const
{
  double const ref_rel_isolation = 0.2;
  GeV const ref_Pt[2] = {10, 15};
  double const ref_eta[2] = {2.1, 2.5};
  bool LooseLeptonValidity = true;
  const TString type[2] = {"muon", "electron"};
  for (ushort type_ind = 0; type_ind < 2; type_ind ++)
  {
    for (ushort ind = 0; ind < processed_event -> GetObjectCount(type[type_ind]); ind ++)
    {
     
      if (lepton == processed_event -> GetObject(type[type_ind], ind)) continue;
      const Lepton * const lepton = (Lepton*) processed_event -> GetObject(type[type_ind], ind);
      const double relative_isolation = lepton -> relative_isolation;
      const GeV Pt = lepton -> Pt();
      const double AbsEta = fabs(lepton -> Eta());
      const bool relative_isolation_valid = relative_isolation > ref_rel_isolation;
      const bool Pt_valid = Pt < ref_Pt[type_ind];
      const bool eta_valid = AbsEta > ref_eta[type_ind];
      LooseLeptonValidity &= (relative_isolation_valid or Pt_valid && eta_valid);
    }
  }
  return LooseLeptonValidity;
}

bool Selector::ValidateBtag() const 
{
  return processed_event -> GetBtagCount() > 0;
}

bool Selector::ValidateTaus() const 
{
  const GeV TAU_PT_MIN       = 20; 
  const double TAU_ETA_MAX   = 2.4;
  vector<Tau*> validated_taus;
  for (unsigned int tau_ind = 0; tau_ind < processed_event -> Taus.size(); tau_ind ++)
  {
    const Tau * const tau = &processed_event -> Taus.at(tau_ind); 
    const double AbsEta     = fabs(tau -> Eta());
    const double tau_Pt      = tau -> Pt();
    const bool tau_Eta_valid = AbsEta < TAU_ETA_MAX;
    const bool tau_Pt_valid  = tau_Pt > TAU_PT_MIN;
    const bool tau_valid = tau_Eta_valid and tau_Pt_valid;
    
    if (tau_valid) validated_taus.push_back(const_cast<Tau*>(tau));
  }
  pure_event.tau = (validated_taus.size() == 1) ? *validated_taus[0] : Tau();
  return validated_taus.size() == 1; 
}

bool Selector::ValidateTauOS() const
{
  const double validatedTauCharge = pure_event.tau.charge;
  const double LeptonCharge = pure_event.lepton.charge;
  return validatedTauCharge * LeptonCharge < 0;  

}

bool Selector::ValidateJets() const
{
  const GeV JET_PT_MIN = 20;
  const double JET_ETA_MAX = 2.4;
  const double JET_LEPTON_DR_MIN = 0.3;
  const GeV JET_PT_MIN2 = 30;
  ushort number_pt_gr_JET_PT_MIN2 = 0;
  for (uint jet_ind = 0; jet_ind < processed_event -> Jets . size(); jet_ind++)  
  {
    const Jet * const jet = &processed_event -> Jets . at(jet_ind);
    
    const double DeltaR = jet -> DeltaR(pure_event.lepton);
    if (DeltaR > JET_LEPTON_DR_MIN){
      const double Pt       = jet -> /*GetPt()*/ Pt();
      const double AbsEta  = fabs(jet -> Eta());
      if (AbsEta < JET_ETA_MAX && Pt > JET_PT_MIN) 
	pure_event.Jets.push_back(*jet);
    }
  } 
  
  for (ushort ind = 0; ind < pure_event.Jets.size(); ind ++)  {
    if (pure_event.Jets[ind] . Pt() > JET_PT_MIN2) number_pt_gr_JET_PT_MIN2 ++; 
  }
  return pure_event.Jets.size() > 2 and number_pt_gr_JET_PT_MIN2 > 1;
}

bool Selector::ValidateMET() const 
{
  const GeV MET_MAX = 40;
  return processed_event -> met.at(0).Pt() > MET_MAX;
}

bool Selector::ValidateEvent()
{
  pure_event = PureEvent();
  LeptonValid = (gVariables::geChONmuChOFF) ? ValidateElectron() : ValidateMuon();
  if (not LeptonValid) return false;
  LooseLeptonValid = ValidateLooseLepton();
  JetValid  = ValidateJets();
  METValid  = ValidateMET();
  BtagValid = ValidateBtag();
  TausValid = ValidateTaus();
  TauOS     = (TausValid) ? ValidateTauOS() : false;
  SelectorStatistics();
  return LeptonValid && JetValid && LooseLeptonValid && METValid && BtagValid && TausValid && TauOS;

}

bool Selector::DeleteHadronisedTauJet() const
{
  const double ref_DeltaR = 0.4;
  bool TauJetFound = false;
  for (ushort ind = 0; ind < pure_event.Jets.size(); ind ++)
  {
    const Jet* const jet = &pure_event.Jets[ind];
    const double DeltaR = jet -> DeltaR(pure_event.lepton);
    if (DeltaR < ref_DeltaR) {
      pure_event.Jets.erase(pure_event.Jets.begin() + ind);
      TauJetFound = true;
      
    }
  }
  return TauJetFound;
}

void Selector::FinishPureEvent()
{
  pure_event.met = processed_event -> met[0];
  pure_event.Vertices = processed_event -> Vertices;
}

void Selector::RunInTestMode()
{
  processed_event -> ls("jet");
  PhysicsObject *jet = processed_event -> GetLeadingJet("Pt", 3);
  printf("Selected jet\n");
  jet -> ListLorentzVector();

}

Selector::~Selector()
{
}
