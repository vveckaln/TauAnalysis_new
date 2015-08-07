#include "LIP/TauAnalysis/interface/UncertaintiesApplicator.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"


#include <math.h>
using namespace cpregister;
using namespace gVariables;
UncertaintiesApplicator::UncertaintiesApplicator(EventSink<DigestedEvent *> *next_processor_stage) : 
EventProcessor<DigestedEvent*, DigestedEvent *>(next_processor_stage)
{

  const TString jecDir = "/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/jec";
  muSCleFitCorrector = getMuonCorrector(jecDir, input_file_name);
  factorizedJetCorrector = utils::cmssw::getJetCorrector(jecDir, not gIsData);

}

void UncertaintiesApplicator::Run()
{
  output_buffer = input_buffer;
  for (uint ind = 0; ind < input_buffer -> size(); ind ++)
  {
    processed_event = input_buffer -> operator[](ind); 
    ApplyMuScleFitCorrector();
    ApplyFactorizedJetCorrector();
    /*processed_event -> SmearJets();
      processed_event -> CorrectMET();*/
   
  }
   if (not output_buffer -> IsEmpty()) ProceedToNextStage();
}

void UncertaintiesApplicator::Report()
{
  ContinueReportToNextStage();
}

void UncertaintiesApplicator::ApplyJESuncertainty() const
{


}

void UncertaintiesApplicator::ApplyMuScleFitCorrector() const
{
  for (unsigned int muon_ind = 0; muon_ind < processed_event -> Muons.size(); muon_ind ++)
    {
      Muon * const muon = (Muon*) processed_event -> GetPhysicsObject("muon", muon_ind);
      muSCleFitCorrector -> applyPtCorrection(*muon , muon -> charge );
      if (not gIsData) 
	muSCleFitCorrector -> applyPtSmearing(*muon, muon -> charge, false);
    }
}

void UncertaintiesApplicator::ApplyFactorizedJetCorrector() const
{
  for(size_t ijet=0; ijet < processed_event -> Jets.size(); ijet++)
    {
      Jet * const jet = (Jet*)processed_event -> 
	GetPhysicsObject("jet", ijet);
      const float toRawSF(jet -> torawsf);
      *jet *= toRawSF;
      factorizedJetCorrector -> setJetEta(jet -> Eta());
      factorizedJetCorrector -> setJetPt(jet -> Pt());
      factorizedJetCorrector -> setJetA(jet -> area);
      factorizedJetCorrector -> setRho(processed_event -> rho);
      const float newJECSF(factorizedJetCorrector -> getCorrection());
      *jet *= newJECSF;
      jet -> torawsf = 1./newJECSF;
    }
}

UncertaintiesApplicator::~UncertaintiesApplicator()
{
  delete muSCleFitCorrector;
  delete factorizedJetCorrector;
}
