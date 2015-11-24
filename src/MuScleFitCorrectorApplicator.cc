#include "CERN_RTU/TauAnalysis/interface/MuScleFitCorrectorApplicator.hh"
#include "CERN_RTU/TauAnalysis/interface/Register.hh"
#include "CERN_RTU/TauAnalysis/interface/GlobalVariables.hh"


#include <math.h>
using namespace cpregister;
using namespace gVariables;
MuScleFitCorrectorApplicator::MuScleFitCorrectorApplicator(EventSink<event_type> *next_processor_stage) : 
EventProcessor<event_type, event_type>(next_processor_stage)
{
  const TString jecDir = gwork_directory + "/data/jec";

  muSCleFitCorrector = getMuonCorrector(jecDir, input_file_name);
}

void MuScleFitCorrectorApplicator::Run()
{
  output_event = input_event; 
  ApplyMuScleFitCorrector();
  ProceedToNextStage();
}

void MuScleFitCorrectorApplicator::Report()
{
  ContinueReportToNextStage();
}

void MuScleFitCorrectorApplicator::ApplyMuScleFitCorrector() const
{
  for (unsigned int muon_ind = 0; muon_ind < input_event -> muons.size(); muon_ind ++)
    {
      pat::Muon * const muon = & input_event -> muons[muon_ind];
      TLorentzVector p4(muon -> px(), muon -> py(), muon -> pz(), muon ->energy());
      muSCleFitCorrector -> applyPtCorrection(p4 , muon -> pdgId() < 0 ? -1 : 1);
      if (not gIsData) 
	muSCleFitCorrector -> applyPtSmearing(p4, muon -> pdgId() < 0 ? -1 : 1, false);
      muon -> setP4(LorentzVector(p4.Px(),p4.Py(),p4.Pz(),p4.E() ) );
    }
}

MuScleFitCorrectorApplicator::~MuScleFitCorrectorApplicator()
{
  delete muSCleFitCorrector;
}
