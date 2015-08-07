#include "LIP/TauAnalysis/interface/FactorisedJetCorrectorApplicator.hh"
#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"


#include <math.h>
using namespace cpregister;
using namespace gVariables;
FactorisedJetCorrectorApplicator::FactorisedJetCorrectorApplicator(EventSink<event_type> *next_processor_stage) : 
EventProcessor<event_type, event_type>(next_processor_stage)
{

  const TString jecDir = "/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/jec";
  factorizedJetCorrector = utils::cmssw::getJetCorrector(jecDir, not gIsData);

}

void FactorisedJetCorrectorApplicator::Run()
{
  output_buffer = input_buffer;
  for (uint ind = 0; ind < input_buffer -> size(); ind ++)
  {
    processed_event = &input_buffer -> operator[](ind);    
    ApplyFactorizedJetCorrector();
    /*processed_event -> SmearJets();
      processed_event -> CorrectMET();*/
   
  }
   if (not output_buffer -> IsEmpty()) ProceedToNextStage();
}

void FactorisedJetCorrectorApplicator::Report()
{
  ContinueReportToNextStage();
}

void FactorisedJetCorrectorApplicator::ApplyJESuncertainty() const
{


}

void FactorisedJetCorrectorApplicator::ApplyFactorizedJetCorrector() const
{
  /*for(size_t ijet=0; ijet < processed_event -> jets.size(); ijet++)
    {
      pat::Jet * const jet = (pat::Jet*)processed_event -> 
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
    }*/
}

FactorisedJetCorrectorApplicator::~FactorisedJetCorrectorApplicator()
{
  delete factorizedJetCorrector;
}
