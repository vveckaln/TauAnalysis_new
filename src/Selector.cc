#include "LIP/TauAnalysis/interface/Selector.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"

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
  for (unsigned short sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)
    {
      TH1D * h = GetStatisticsHistogram(sample_ind); 
      TAxis *xaxis = h -> GetXaxis();
      for (int binind = 1; binind <= xaxis -> GetNbins(); binind ++)
	{
	  xaxis -> SetBinLabel(binind, Selector_report_Xaxis_labels[binind - 1]);
	}
    }
}

void Selector::Run()
{
  output_buffer = new EventBuffer<PureEvent*>(10, "independent");
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
	  printf("---------------- NEXT EVENT-----------------------\n");
      
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

TH1D * const Selector::GetStatisticsHistogram(const unsigned short sample_ind)
{
  return (TH1D*)hstruct_worker -> GetHStructure(samples_names[sample_ind], "numb_events_selection_stagesSELECTOR_BASE") -> GetRef(); 
}

void Selector::CollectStatistics()
{
  
  TH1D * const h = GetStatisticsHistogram(number_active_sample);
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
  for (unsigned short sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)
    {
      printf("Selector report SELECTOR_BASE %s\n", samples_names[sample_ind].Data());
      TH1D * const h = GetStatisticsHistogram(sample_ind);
            h -> LabelsDeflate();

      printf("%s %s %f\n", h-> GetName(), h -> GetTitle(), h -> GetEntries());
      Table table("Selector_report_SELECTOR_BASE");
      TString table_name = gOutputDirectoryName + "/Tables/" + TString(gSystem -> BaseName(input_file_names[0].c_str())).ReplaceAll(".root", "") + "_report_SELECTOR_BASE.txt";

      table.FillFromLabeledHistogram(h);
      table.ls();
      table.Save(table_name);
      
    
    }
  ContinueReportToNextStage();

}

bool Selector::ValidateElectron() const
{
  
  Electron * const electron = (Electron*)processed_event -> GetLeadingLepton("electronmuon");
  if (electron == NULL) return false;
  const bool electron_valid = (electron -> title == TString("electron"));

  if (electron_valid)
    {
      pure_event.lepton = *electron;
      lepton = electron;
    }
  return electron_valid;
}
 
bool Selector::ValidateMuon() const
{
  
  Muon * const muon = (Muon*)processed_event -> GetLeadingLepton("muon");
  if (muon == NULL) return false;
  const bool muon_valid = (muon -> title == TString("muon"));

  if (muon_valid)
    {
      pure_event.lepton = (Lepton)*muon;
      lepton = muon;
    }
  return muon_valid;
}

bool Selector::ValidateLooseLepton() const
{
  nVeto_electrons                      = 0;
  nVeto_muons                          = 0;
  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("LOOSE LEPTON VALIDATION\n");
    }
  double const ref_rel_isolation        = 0.2;
  GeV const    ref_Pt[2]                = {10, 15};
  double const ref_eta[2]               = {2.5, 2.5};
  const double ETA_EXCLUSION_REGION_MIN = 1.4442;
  const double ETA_EXCLUSION_REGION_MAX = 1.5660;
  bool LooseLeptonValidity              = true;
  const TString type[2]                 = {"muon", "electron"};
  unsigned short test_lepton_n = 0;
  for (ushort type_ind = 0; type_ind < 2; type_ind ++)
    {
      for (ushort ind = 0; ind < processed_event -> GetObjectCount(type[type_ind]); ind ++)
	{
     
	  const Lepton * const lepton = (Lepton*) processed_event -> GetObject(type[type_ind], ind);
	  if (this -> lepton == lepton) continue;
	  test_lepton_n ++;
	  if (IsSingleMuPD and lepton -> title == "electron") return false;
	  const double relative_isolation       = lepton -> relative_isolation;
	  const GeV    Pt                       = lepton -> Pt();
	  const double AbsEta                   = lepton -> title == "electron" ? 
	    fabs(((Electron*)lepton) -> el_info.sceta) : fabs(lepton -> Eta());
	  const bool   relative_isolation_valid = relative_isolation < ref_rel_isolation;
	  const bool   Pt_valid                 = Pt > ref_Pt[type_ind];
	  bool   eta_valid                      = AbsEta < ref_eta[type_ind];
	  const Int_t  idbits(lepton -> idbits);
	  bool passID = true;
	  if(lepton -> title == "electron")
	    {
	      if (AbsEta > ETA_EXCLUSION_REGION_MIN and AbsEta < ETA_EXCLUSION_REGION_MAX) eta_valid = false;
	      if( ((Electron*)lepton) -> el_info.isConv) passID = false;
	      const bool isLoose ((idbits >> 4) & 0x1);
	      if (!isLoose) 
		passID = false;
	    }
	  else
	    {
	      const bool isLoose ((idbits >> 8) & 0x1);
	      if(!isLoose) 
		passID = false;
	      
	    }
	  if (passID and relative_isolation_valid and Pt_valid and eta_valid)
	    {
	      if (lepton -> title == "electron") 
		nVeto_electrons ++;
	      if (lepton -> title == "muon") 
		nVeto_muons++;
	    }
	  if (print_mode)
	    {
	      printf("listing loose lepton\n");
	      lepton -> ls("verbose");
	      printf("PassID valid %s Relative isolation valid = %s, Pt valid = %s, Eta valid = %s\n", 
		     passID                   ? "true" : "false",
		     relative_isolation_valid ? "true" : "false",
		     Pt_valid                 ? "true" : "false",
		     eta_valid                ? "true" : "false");
	    }

	}
      //printf("test_lepton_n %u\n", test_lepton_n);
    }
  
  LooseLeptonValidity = not (nVeto_electrons > 0 or nVeto_muons > 0);
  if (print_mode)
    {
      printf("LOOSE LEPTON VALID = %s\n", LooseLeptonValidity ? "true" : "false");
    }
  return LooseLeptonValidity;
}

bool Selector::ValidateBtag() const 
{
  const unsigned char BtagCount = processed_event -> GetBtagCount(pure_event.lepton);
  const bool btag_count_valid = BtagCount > 0;
  
  if (print_mode)
    {
      printf("* * * * * * * * * * * * * * * * * \n");
      printf("VALIDATING BTAG COUNT\n");
      printf("Btag count = %u\n", BtagCount);
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
 
  unsigned short valid_taus  = 0;
  for (unsigned short tau_ind = 0; tau_ind < processed_event -> Taus.size(); tau_ind ++)
    {
      
      const bool tau_valid = processed_event -> ValidateTau(tau_ind, &pure_event.lepton );
      
      if (tau_valid)
	{
	  valid_taus ++;
	  pure_event.tau = processed_event -> Taus[tau_ind];
	}
    }
  
  const bool Taus_valid = valid_taus == 1;
  
  if (print_mode)
    {
      printf("number of validates taus : %u\n", valid_taus);
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
  
  const GeV JET_PT_MIN2           = 30;
  ushort number_pt_gr_JET_PT_MIN2 = 0;
  for (uint jet_ind = 0; jet_ind < processed_event -> Jets . size(); jet_ind++)  
    {
      const Jet * const jet = &processed_event -> Jets . at(jet_ind);
      const bool Jet_valid    = processed_event -> ValidateJet(jet_ind, pure_event.lepton);
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
  /*printf("************* NEXT EVENT *************\n");
    printf(" %u %u %u %f\n", processed_event -> Run, processed_event -> Lumi, processed_event -> Event, processed_event -> pileup_corr_weight);*/

  pure_event = PureEvent();
  LeptonValid = (gVariables::geChONmuChOFF) ? ValidateElectron() : ValidateMuon();
  if (not LeptonValid) return false;
  LooseLeptonValid = ValidateLooseLepton();
  //processed_event -> DeleteTauJet(&pure_event.lepton);
  JetValid  = ValidateJets();
  
  //printf("Jet valid %s\n", JetValid ? "true" : "false");
  //printf("nVeto_electrons %u nVeto_muons %u\n", nVeto_electrons , nVeto_muons );
  if (not (JetValid and LooseLeptonValid and LeptonValid)) return false;
  //printf("passed first criterion \n");
 
  //getchar();
  METValid  = ValidateMET();
  if (not METValid) return false;
  /*printf("passed MET criterion");
    getchar();*/
  BtagValid = ValidateBtag();
  if (not BtagValid) return false;
  //printf("passed btag criterion\n");
  //getchar();
  TausValid = ValidateTaus();
  //getchar();
  if (not TausValid) return false;
  //printf("passed tau criterion\n");
  //getchar();
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
  pure_event.pileup_corr_weight = processed_event -> pileup_corr_weight;
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
