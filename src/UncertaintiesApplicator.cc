#include "LIP/TauAnalysis/interface/UncertaintiesApplicator.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"

#include <math.h>
using namespace cpHistogramPoolRegister;
using namespace cpFileRegister;
UncertaintiesApplicator::UncertaintiesApplicator(EventSink<DigestedEvent *> *next_processor_stage) : 
EventProcessor<DigestedEvent*, DigestedEvent *>(next_processor_stage)
{
  const TString jecDir = "/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_15/src/LIP/TauAnalysis/data/jec";
  muSCleFitCorrector = getMuonCorrector(jecDir, input_file_name);

}

void UncertaintiesApplicator::Run()
{
  output_buffer = input_buffer;
  for (uint ind = 0; ind < input_buffer -> size(); ind ++)
  {
    processed_event = input_buffer -> operator[](ind); 
    for (unsigned int muon_ind = 0; muon_ind < processed_event -> Muons.size(); muon_ind ++)
      {
	Muon * const muon = & processed_event -> Muons[muon_ind];
	muSCleFitCorrector -> applyPtCorrection(*muon , muon -> charge );
	if (not isData) 
	  muSCleFitCorrector -> applyPtSmearing(*muon, muon -> charge, false);
      }
    processed_event -> SmearJets();
    processed_event -> CorrectMET();
   
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

UncertaintiesApplicator::~UncertaintiesApplicator()
{
  delete muSCleFitCorrector;
}
