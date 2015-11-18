#include "LIP/TauAnalysis/interface/SamplesCatalogue.hh"

const unsigned short generic_samples_count = 1;

const TString generic_samples_names[generic_samples_count] = 
  {
    "generic_name"
  };

const unsigned short ttbar_samples_count = 8;

const TString ttbar_samples_names[ttbar_samples_count] = 
  {
    "muon_tau",
    "lepton_jets",
    "dilepton_muon_electron",
    "dilepton_muon_muon",
    "tau_jets",
    "tau_tau",
    "hadronic",
    generic_samples_names[0]
  };

const unsigned short DY_samples_count = 3;

const TString DY_samples_names[DY_samples_count] = 
  {
    "lepton_lepton_jets",
    "tau_tau_jets",
    generic_samples_names[0]
  };
