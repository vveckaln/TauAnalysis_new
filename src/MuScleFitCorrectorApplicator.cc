#include "LIP/TauAnalysis/interface/MuScleFitCorrectorApplicator.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"


#include <math.h>
using namespace cpregister;
using namespace gVariables;
MuScleFitCorrectorApplicator::MuScleFitCorrectorApplicator(EventSink<ReadEvent_llvv> *next_processor_stage) : 
EventProcessor<ReadEvent_llvv, ReadEvent_llvv>(next_processor_stage)
{
  const TString jecDir = "/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/jec";

  muSCleFitCorrector = getMuonCorrector(jecDir, input_file_name);
}

void MuScleFitCorrectorApplicator::Run()
{
  output_buffer = input_buffer;
  for (uint ind = 0; ind < input_buffer -> size(); ind ++)
  {
    processed_event = &input_buffer -> operator[](ind); 
    ApplyMuScleFitCorrector();
       
  }
   if (not output_buffer -> IsEmpty()) ProceedToNextStage();
}

void MuScleFitCorrectorApplicator::Report()
{
  ContinueReportToNextStage();
}

void MuScleFitCorrectorApplicator::ApplyMuScleFitCorrector() const
{
  for (unsigned int muon_ind = 0; muon_ind < processed_event -> muons.size(); muon_ind ++)
    {
      pat::Muon * const muon = (pat::Muon*) processed_event -> GetObject("muon", muon_ind);
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
