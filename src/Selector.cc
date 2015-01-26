#include "LIP/TauAnalysis/interface/Selector.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/Parser.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
#include "LIP/TauAnalysis/interface/llvvObjects.h"
#include "LIP/TauAnalysis/interface/Table.h"
#include "DataFormats/Math/interface/deltaR.h"

#include <math.h>
#include "TCanvas.h"
using namespace cpFileRegister;

const short Selector::report_size = 8;
const char *Selector::Selector_report_Xaxis_labels[report_size] = 
    {
      "events recieved",
      "1 lept",
      "passed loose lepton veto",
      "#geq 3 jets", 
      "E^{miss}_{T}", 
      "#geq 1btag", 
      "1#tau", 
      "OS"
    };

Selector::Selector(EventSink<PureEvent *> *next_processor_stage):EventProcessor<DigestedEvent*, PureEvent *>(next_processor_stage)
{
  mapOfSelectorHistoPools = new MapOfObjectPools<TH1D>();
  vector<HistogramDescriptor> * selector_h_descriptors = LoadHistogramDescriptors("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/histogram_specifiers/spec_selector_histograms.xml");
  HistogramPool * base_pool = new HistogramPool(selector_h_descriptors, "SELECTOR_BASE");
  base_pool -> SetDirectoryName("SELECTOR_BASE");
  mapOfSelectorHistoPools -> Add((ObjectPool<TH1D>*)base_pool);
  TH1D * h = base_pool -> at("numb_events_selection_stages");// -> SetBit(TH1::kCanRebin);
  TAxis *xaxis = h -> GetXaxis();
  for (int binind = 1; binind <= xaxis -> GetNbins(); binind ++)
    {
      xaxis -> SetBinLabel(binind, Selector_report_Xaxis_labels[binind - 1]);
    }

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
      processed_event -> CorrectMET();
      Reset();
      validated_jets.clear();
      lepton = NULL;
      print_mode = false;
      //Run 190688, lumi 99, evId 22420320



      //if (processed_event -> Run == 190688 and processed_event -> Lumi == 99 and processed_event -> Event == 22420320) print_mode = true;
      //if (not print_mode) continue;
      if (print_mode)
	{
	  printf("EVENT IDENTITY %u %u %u\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event);
	  processed_event -> ls("electron");
	  processed_event -> ls("muon");
	  printf("Listing leading lepton\n");
	  processed_event -> GetLeadingLepton("electronmuon") -> ls("verbose");
	}
      bool event_validated = ValidateEvent();

      if (print_mode)
	{
	  printf("EVENT VALID %s\n", event_validated ? "true" : "false");
	  printf("---------------- NEXT -----------------------\n");
      
          getchar();
	}
      CollectStatistics();
      if (event_validated) 
	{
	  //printf("%u %u %u\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event);
	  DeleteHadronisedTauJet();
	  FinishPureEvent();
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

void Selector::Reset()
{
  LeptonValid      = false;
  LooseLeptonValid = false;
  JetValid         = false;
  BtagValid        = false;
  METValid         = false;
  TausValid        = false;
  TauOS            = false;

}

TH1D * const Selector::GetStatisticsHistogram()
{
  const TString title = (uncertainties_activated) ? 
    "SELECTOR_" + TString(uncertainty_name[uncertainty_signal]) + "_" + 
    TString(uncertainty_subname[uncertainty_subsignal]) : "SELECTOR_BASE";
  return mapOfSelectorHistoPools -> GetObjectPool(title) 
    -> at("numb_events_selection_stages");
}

void Selector::CollectStatistics()
{
  
  TH1D * const h = GetStatisticsHistogram();
  const double weight = processed_event -> pileup_corr_weight;
  
  h -> Fill(Selector_report_Xaxis_labels[0], weight); 
  if (LeptonValid)
    h -> Fill(Selector_report_Xaxis_labels[1], weight); else return;
  if (LooseLeptonValid)
    h -> Fill(Selector_report_Xaxis_labels[2], weight); else return;
  if (JetValid) 
    h -> Fill(Selector_report_Xaxis_labels[3], weight); else return; 
  if (METValid) 
    h -> Fill(Selector_report_Xaxis_labels[4], weight); else return;
  if (BtagValid)
    h -> Fill(Selector_report_Xaxis_labels[5], weight); else return;
  if (TausValid)
    h -> Fill(Selector_report_Xaxis_labels[6], weight); else return;
  if (TauOS)
    h -> Fill(Selector_report_Xaxis_labels[7], weight); else return; 
}

void Selector::Report()
{
  printf("Selector report SELECTOR_BASE\n");
  TH1D * const h = GetStatisticsHistogram();
  //h -> LabelsDeflate();
  Table table("Selector_report_SELECTOR_BASE");
  TString table_name = gOutputDirectoryName + "/Tables/" + TString(gSystem -> BaseName(input_file_names[0].c_str())).ReplaceAll(".root", "") + "_report_SELECTOR_BASE.txt";

  table.FillFromLabeledHistogram(h);
  table.ls();
  table.Save(table_name);
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

  output_file -> cd();
  h -> Write();
  
  ContinueReportToNextStage();

}

bool Selector::ValidateElectron() const
{
  double const ref_rel_isolation        = 0.15;

  const GeV ELECTRON_PT_MIN             = 35;
  const double ELECTRON_ETA_MAX         = 2.5;
  const double ETA_EXCLUSION_REGION_MIN = 1.4442;
  const double ETA_EXCLUSION_REGION_MAX = 1.5660;
  Electron * const electron = (Electron*)processed_event -> GetLeadingLepton("electron");
  if (electron == NULL) return false;
  const double relative_isolation       = electron -> relative_isolation;
  const double AbsEta                   = fabs(electron -> Eta());
  const GeV  Pt                         = electron -> Pt();
  const bool relative_isolation_valid   = relative_isolation > ref_rel_isolation;
  const bool Eta_valid                  = AbsEta < ELECTRON_ETA_MAX;
  const bool Pt_valid                   = Pt > ELECTRON_PT_MIN;
  const bool outside_eta_exclusion_region = AbsEta < ETA_EXCLUSION_REGION_MIN or AbsEta > ETA_EXCLUSION_REGION_MAX;
  
  bool passID = true;
  if (electron -> el_info.isConv) passID = false;
  const bool MVATriggerV0(electron -> el_info.mvatrigv0 > 0.5); 
  if (not MVATriggerV0) passID = false;
  
  const bool electron_valid = Eta_valid and Pt_valid and outside_eta_exclusion_region and passID and relative_isolation_valid;

  if (electron_valid)
    {
      pure_event.lepton = *electron;
      lepton = electron;
    }
  return electron_valid;
}
 
bool Selector::ValidateMuon() const
{
  double const ref_rel_isolation = 0.2;
  const GeV MUON_PT_MIN          = 30;
  const double MUON_ETA_MAX      = 2.1;
  Muon * const muon = (Muon*)processed_event -> GetLeadingLepton("muon");
  if (muon == NULL) return false;
  const double relative_isolation     = muon -> relative_isolation;
  const double AbsEta                 = fabs(muon -> Eta());
  const GeV  Pt                       = muon -> Pt();
  const bool relative_isolation_valid = relative_isolation < ref_rel_isolation;
  const bool Eta_valid                = AbsEta < MUON_ETA_MAX;
  const bool Pt_valid                 = Pt > MUON_PT_MIN;
  
  bool passID = true;;
  bool isTight ((muon -> idbits >> 10) & 0x1);
  if(!isTight) passID = false;

  const bool muon_valid = Eta_valid and Pt_valid and passID and relative_isolation_valid;
  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("LEADING LEPTON VALIDATION:\n");
      printf("Eta valid = %s, Pt valid %s, passID valid = %s, relative_isolation_valid = %s\n",
      Eta_valid                ? "true" : "false",
      Pt_valid                 ? "true" : "false",
      passID                   ? "true" : "false",
      relative_isolation_valid ? "true" : "false");
      printf("LEADING LEPTON VALID = %s\n", muon_valid ? "true" : "false");
    }
  if (muon_valid)
  {
    pure_event.lepton = (Lepton)*muon;
    lepton = muon;
  }
  return muon_valid;
}

bool Selector::ValidateLooseLepton() const
{
  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("LOOSE LEPTON VALIDATION\n");
    }
  double const ref_rel_isolation = 0.2;
  GeV const ref_Pt[2] = {10, 15};
  double const ref_eta[2] = {2.1, 2.5};
  bool LooseLeptonValidity = true;
  const TString type[2] = {"muon", "electron"};
  for (ushort type_ind = 0; type_ind < 2; type_ind ++)
  {
    for (ushort ind = 0; ind < processed_event -> GetObjectCount(type[type_ind]); ind ++)
    {
     
      const Lepton * const lepton = (Lepton*) processed_event -> GetObject(type[type_ind], ind);
      if (this -> lepton == lepton) continue;
      
      const double relative_isolation     = lepton -> relative_isolation;
      const GeV    Pt                     = lepton -> Pt();
      const double AbsEta                 = fabs(lepton -> Eta());
      const bool relative_isolation_valid = relative_isolation < ref_rel_isolation;
      const bool Pt_valid                 = Pt > ref_Pt[type_ind];
      const bool eta_valid                = AbsEta < ref_eta[type_ind];
      LooseLeptonValidity &= not (relative_isolation_valid and Pt_valid and eta_valid);
      if (print_mode)
	{
	  printf("listing loose lepton\n");
	  lepton -> ls("verbose");
	  printf("Relative isolation valid = %s, Pt valid = %s, Eta valid = %s\n", 
		 relative_isolation_valid ? "true" : "false",
		 Pt_valid                 ? "true" : "false",
		 eta_valid                ? "true" : "false");
	}

    }
  }
  
  if (print_mode)
    {
      printf("LOOSE LEPTON VALID = %s\n", LooseLeptonValidity ? "true" : "false");
    }
  return LooseLeptonValidity;
}

bool Selector::ValidateBtag() const 
{
  unsigned char BtagCount = 0;
  for (unsigned short ind = 0; ind < validated_jets.size(); ind ++)
    {
   
      if (validated_jets[ind].BTagSFUtil_isBtagged) BtagCount ++;
    }
  
  const bool btag_count_valid = BtagCount > 0;
  
  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("VALIDATING BTAG COUNT\n");
      printf("Btag count = %u\n", processed_event -> GetBtagCount());
      printf("BTAG COUNT VALID %s\n", btag_count_valid ? "true" : "false");
    }
  return btag_count_valid;
}

bool Selector::ValidateTaus() const 
{
  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("VALIDATING TAUS\n");
    }
 
  const GeV TAU_PT_MIN       = 20; 
  const double TAU_ETA_MAX   = 2.4;
  vector<Tau*> validated_taus;
  for (unsigned int tau_ind = 0; tau_ind < processed_event -> Taus.size(); tau_ind ++)
    {
      const Tau * const tau = &processed_event -> Taus.at(tau_ind); 
      const double AbsEta                  = fabs(tau -> Eta());
      const double tau_Pt                  = tau -> Pt();
      if(tau_Pt < 20.0 || AbsEta > 2.3) continue;
      const bool tau_Eta_valid             = AbsEta < TAU_ETA_MAX;
      const bool tau_Pt_valid              = tau_Pt > TAU_PT_MIN;
      const bool againstElectronMediumMVA5 = tau -> passID(llvvTAUID::againstElectronMediumMVA5);
      const bool againstMuonTight2         = tau -> passID(llvvTAUID::againstMuonTight2);
      const bool decayModeFinding          = tau -> passID(llvvTAUID::decayModeFinding);
      const bool byMediumCombinedIsolationDeltaBetaCorr3Hits = tau -> passID(llvvTAUID::byMediumCombinedIsolationDeltaBetaCorr3Hits);
      const bool passID   = againstElectronMediumMVA5 and againstMuonTight2 and decayModeFinding and byMediumCombinedIsolationDeltaBetaCorr3Hits;
      //printf("%f %f\n", tau -> dZ, tau -> emfraction);
      //getchar();
      const double tau_lepton_deltaR       = tau -> DeltaR(pure_event.lepton);
	//deltaR(*tau, pure_event.lepton);
      const bool overlapwithlepton         = tau_lepton_deltaR < 0.1;
      const bool dZvalid                   = abs(tau -> dZ) < 0.5; 
      const bool emfraction_valid          = tau -> emfraction < 2;
      const bool tau_valid                 = tau_Eta_valid and tau_Pt_valid and passID and tau -> isPF and dZvalid and emfraction_valid and not overlapwithlepton;
      
      if (print_mode)
	{
	  printf("listing Tau\n");
	  tau -> ls("verbose");
	  printf("Eta valid = %s, Pt valid = %s, \n againstElectronMediumMVA5 = %s, againstMuonTight2 = %s, decayModeFinding = %s, byMediumCombinedIsolationDeltaBetaCorr3Hits = %s\n isPF %s, dZ %f, emfraction %f", 
		 tau_Eta_valid                    ? "true" : "false", 
		 tau_Pt_valid                     ? "true" : "false", 
		 againstElectronMediumMVA5        ? "true" : "false",
		 againstMuonTight2                ? "true" : "false",
		 decayModeFinding                 ? "true" : "false",
		 byMediumCombinedIsolationDeltaBetaCorr3Hits
		 ? "true" : "false",		 
		 tau -> isPF                      ? "true" : "false",
		 abs(tau -> dZ), tau -> emfraction);
	  printf("Tau valid = %s\n", tau_valid ? "true" : "false");
	}
      if (tau_valid) validated_taus.push_back(const_cast<Tau*>(tau));
    }
  pure_event.tau = (validated_taus.size() == 1) ? *validated_taus[0] : Tau();
  const bool Taus_valid = validated_taus.size() == 1;
  
  if (print_mode)
    {
      printf("number of validates taus : %lu\n", validated_taus.size());
      printf("TAUS VALID = %s\n", Taus_valid ? "true" : "false");
    }
  return Taus_valid; 
}

bool Selector::ValidateTauOS() const
{
  
  const double validatedTauCharge = pure_event.tau.charge;
  const double LeptonCharge = pure_event.lepton.charge;
  const bool OS_valid = validatedTauCharge * LeptonCharge < 0;

  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("VALIDATING OS\n");
      printf("listing  tau\n");
      pure_event.tau.ls("verbose");
      printf("listing lepton\n");
      lepton -> ls("verbose");
      printf("OS VALID %s\n", OS_valid ? "true" : "false");
    }
  return OS_valid;  

}

bool Selector::ValidateJets() const
{
  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("VALIDATING JETS\n");
      printf("Listing lepton against which DeltaR will be compared\n");
      lepton -> ls();
    }
  const GeV JET_PT_MIN            = 20;
  const double JET_ETA_MAX        = 2.4;
  const double JET_LEPTON_DR_MIN  = 0.4;
  const GeV JET_PT_MIN2           = 30;
  ushort number_pt_gr_JET_PT_MIN2 = 0;
  for (uint jet_ind = 0; jet_ind < processed_event -> Jets . size(); jet_ind++)  
    {
      const Jet * const jet = &processed_event -> Jets . at(jet_ind);
      
      const double DeltaR     = jet -> DeltaR(pure_event.lepton);
      const double Pt         = jet -> /*GetPt()*/ Pt();
      const double AbsEta     = fabs(jet -> Eta());
      if (Pt < 15 or AbsEta > 4.7) continue; 
      const bool DeltaR_valid = DeltaR > JET_LEPTON_DR_MIN;
      const bool Eta_valid    = AbsEta < JET_ETA_MAX;
      const bool Pt_valid     = Pt > JET_PT_MIN;
      const bool passPFloose  = (jet -> idbits >> 0) & 0x1;
      const int  puId         = (jet -> idbits >> 3) & 0xf;
      const bool passLoosePuId= (puId >> 2) & 0x1;
      const bool Jet_valid    = DeltaR_valid and Eta_valid and Pt_valid and passPFloose and passLoosePuId;

      if (print_mode)
	{
	  printf("listing jet %u\n", jet_ind);
	  jet -> ls("verbose");
	  printf("DeltaR = %f, lepton Eta = %f, lepton Phi = %f\n", DeltaR, pure_event.lepton.Eta(), pure_event.lepton.Phi());
	  printf("DeltaR valid = %s, Eta valid = %s, Pt valid = %s, passPFloose = %s, passLoosePuId = %s\n", 
		 DeltaR_valid ? "true" : "false",
		 Eta_valid    ? "true" : "false",
		 Pt_valid     ? "true" : "false",
		 passPFloose  ? "true" : "false",
		 passLoosePuId? "true" : "false");
	  printf("Jet valid = %s\n", Jet_valid ? "true" : "false");
	}
      if (Jet_valid) validated_jets.push_back(*jet);
    
    } 
  
  for (ushort ind = 0; ind < validated_jets.size(); ind ++)  
    {
      if (validated_jets[ind] . Pt() > JET_PT_MIN2) number_pt_gr_JET_PT_MIN2 ++; 
    }
  const bool Jets_valid = validated_jets.size() > 2 and number_pt_gr_JET_PT_MIN2 > 1;
  
  if (print_mode)
    {
      printf("Total valid Jet count = %lu, Pt > 30 GeV : %u\n", pure_event.Jets.size(), number_pt_gr_JET_PT_MIN2);
      printf("JETS VALID = %s\n", Jets_valid ? "true" : "false"); 
    }
  
  return Jets_valid;
}

bool Selector::ValidateMET() const 
{
  const GeV MET_MAX = 40;
  const bool MET_valid = processed_event -> met.at(0).Pt() > MET_MAX;
  
  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("VALIDATING MET\n");
      printf("Listing MET\n");
      processed_event -> met.at(0).ls();
      printf("MET VALID = %s\n", MET_valid ? "true" : "false");
    }
  return MET_valid;
}

bool Selector::ValidateEvent()
{
  pure_event = PureEvent();
  LeptonValid = (gVariables::geChONmuChOFF) ? ValidateElectron() : ValidateMuon();
  if (not LeptonValid) return false;
  LooseLeptonValid = ValidateLooseLepton();
  JetValid  = ValidateJets();
  if (not (JetValid and LooseLeptonValid and LeptonValid)) return false;
  METValid  = ValidateMET();
  if (not METValid) return false;    
  BtagValid = ValidateBtag();
  if (not BtagValid) return false;
  TausValid = ValidateTaus();
  if (not TausValid) return false;
  TauOS     = ValidateTauOS(); 
  return TauOS;

}

bool Selector::DeleteHadronisedTauJet() const
{
  const double ref_DeltaR = 0.4;
  bool TauJetFound = false;
  for (ushort ind = 0; ind < pure_event.Jets.size(); ind ++)
  {
    const Jet* const jet = &pure_event.Jets[ind];
    const double DeltaR = jet -> DeltaR(pure_event.tau);
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
