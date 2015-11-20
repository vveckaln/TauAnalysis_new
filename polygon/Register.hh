#ifndef _Register_hh
#define _Register_hh

#include "LIP/TauAnalysis/interface/HistogramPool.hh"
#include "LIP/TauAnalysis/interface/THStackPool.hh"
#include "LIP/TauAnalysis/interface/TCanvasPool.hh"
#include "LIP/TauAnalysis/interface/TGraphPool.hh"
#include "LIP/TauAnalysis/interface/MapOfObjectPools.hh"
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
  extern HStructure_TFile * active_HStructure_TFile;
  extern HStructure_worker * hstruct_worker;
  extern HistogramPool *histogram_pool;
  extern MapOfObjectPools<TH1D> *mapOfHistogramPools; 
  extern MapOfObjectPools<TH1D> *mapOfSelectorHistoPools; 
  extern MapOfObjectPools<TH1D> *mapOfChannelGateHistoPools; 

  extern HistogramPool *data_histo_pool;
  extern HistogramPool *Selector_report_pool;
  extern HistogramPool *Selector_data_report_pool;
  extern THStackPool   *THStack_pool;
  extern TCanvasPool   *TCanvas_pool;
  extern TGraphPool    *TGraph_pool;
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
#include "LIP/TauAnalysis/interface/templates/test.tpp"

#endif
