#ifndef _Register_hh
#define _Register_hh

#include "TApplication.h"
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"
#include "LIP/TauAnalysis/interface/DataSampleDescriptor.hh"

#include "CondFormats/JetMETObjects/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include <vector>
using namespace std;
class HStructure_TFile;
class HStructure_worker;
namespace cpregister
{
  //********************* CENTRAL PROCESSOR HISTOGRAM POOL REGISTER ******
  extern TString     input_file_name;
  extern TFile     * input_file;
  extern vector<string> input_file_names;
  extern TString     output_file_name;
  extern TFile     * output_file;

  extern HStructure_TFile * active_HStructure_TFile;
  extern HStructure_worker * hstruct_worker;
 
  extern vector<HistogramDescriptor> * object_descriptors;
  extern vector<HistogramDescriptor> * selector_h_descriptors;
  extern vector<HistogramDescriptor> * selector_data_h_descriptors;

  extern vector<DataSampleDescriptor> * MCdatasample_descriptors;
  extern vector<DataSampleDescriptor> * datasample_descriptors;
  extern TApplication  application;
  
  extern JetResolution *stdEtaResol;
  extern JetResolution *stdPhiResol; 
  extern JetResolution *stdPtResol; 
  extern JetCorrectionUncertainty * jetCorrectionUncertainty;
  extern fwlite::ChainEvent * fwlite_ChainEvent_ptr;
  extern edm::LumiReWeighting* gLumiWeights[2];
  extern const unsigned short * number_of_samples;
  extern unsigned short number_active_sample;
  extern const TString * samples_names;
  extern bool IsTTbarMC;
  extern bool IsSingleMuPD;
  extern bool IsDY;
  extern bool IstW;
  extern bool IsGeneric;
  extern bool IsWJets;
  //********************** PROGRAMMED UNCERTAINTIES **********************
  extern const uint number_uncertainties;
  extern const uint number_subuncertainties;
  extern const char* uncertainty_name[];
  extern const char* uncertainty_subname[2];

  enum uncertainty_identifiers {JES, JER, BTAG, UNBTAG};
  enum uncertainty_subidentifiers {PLUS, MINUS};
  extern bool signal_uncertainties_transition;
  extern bool uncertainties_activated;
  extern int uncertainty_signal;
  extern int uncertainty_subsignal;
  //********************** SIGNALS TO FORK *******************************
  extern bool fork_activated;
}

#endif
