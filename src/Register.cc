#include "LIP/TauAnalysis/interface/Register.hh"

namespace cpregister
{
  TString                        input_file_name;
  TFile                        * input_file                 = NULL;
  vector<string>                 input_file_names;
  TString                        output_file_name;
  TFile                        * output_file                = NULL;
  HStructure_TFile             * active_HStructure_TFile    = NULL;
  HStructure_worker            * hstruct_worker             = NULL;
  
  vector<HistogramDescriptor>  * object_descriptors         = NULL;
  vector<HistogramDescriptor>  * selector_h_descriptors     = NULL;
  vector<HistogramDescriptor>  * selector_data_h_descriptors= NULL;

  vector<DataSampleDescriptor> * MCdatasample_descriptors   = NULL;
  vector<DataSampleDescriptor> * datasample_descriptors     = NULL;

  JetResolution                * stdEtaResol                = NULL;
  JetResolution                * stdPhiResol                = NULL; 
  JetResolution                * stdPtResol                 = NULL; 
  JetCorrectionUncertainty     * jetCorrectionUncertainty   = NULL;
  fwlite::ChainEvent           * fwlite_ChainEvent_ptr;
  edm::LumiReWeighting         * gLumiWeights[2];
  TApplication                   application("myapp", 0, 0);
  const unsigned short         * number_of_samples          = NULL;
  unsigned short                 number_active_sample;
  const TString                * samples_names              = NULL;
  bool                           IsTTbarMC                  = false;
  bool                           IsSingleMuPD               = false;
  bool                           IsDY                       = false;
  bool                           IstW                       = false;
  bool                           IsGeneric                  = false;
  //********************** PROGRAMMED UNCERTAINTIES **********************
  extern const uint number_uncertainties = 2;
  extern const uint number_subuncertainties = 2;
  extern const char* uncertainty_name[] = {"JES", "JER", "BTAG", "UNBTAG"};
  extern const char* uncertainty_subname[2] = {"PLUS", "MINUS"};
  extern bool signal_uncertainties_transition = false;
  extern bool uncertainties_activated = false;
  extern int uncertainty_signal = 0;
  extern int uncertainty_subsignal = 0;
  //********************** SIGNALS TO FORK *******************************
  extern bool fork_activated = false;
}
