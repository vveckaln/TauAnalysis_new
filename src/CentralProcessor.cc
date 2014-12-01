#include "LIP/TauAnalysis/interface/CentralProcessor.hh"
//#include "LIP/TauAnalysis/interface/HistogramPlotter.hh"
#include "LIP/TauAnalysis/interface/ReadEvent.hh"
#include "LIP/TauAnalysis/interface/FileReader.hh"
#include "LIP/TauAnalysis/interface/EventConverter.hh"
#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"
#include "LIP/TauAnalysis/interface/BTagger.hh"
#include "LIP/TauAnalysis/interface/Selector.hh"
/*#include "LIP/TauAnalysis/interface/KINbHandler.hh"
#include "LIP/TauAnalysis/interface/Fork.hh"
#include "LIP/TauAnalysis/interface/Purge.hh"*/

/*#include "LIP/TauAnalysis/interface/HistogramFiller.hh"
  #include "LIP/TauAnalysis/interface/UncertaintiesNode.hh"*/
#include "LIP/TauAnalysis/interface/PileUpCorrector.hh"

#include "LIP/TauAnalysis/interface/UncertaintiesApplicator.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
#include "LIP/TauAnalysis/interface/Parser.hh"
#include "TLegend.h"
#include "TROOT.h"

using namespace cpFileRegister;
using namespace cpHistogramPoolRegister;

CentralProcessor::CentralProcessor(){
  //  gc_gConfiguration = new GlobalConfiguration();
  
}

void CentralProcessor::Process(const char* option)
{
  isData = false;
  /*isData = (TString(option) == "spy_data") ? true : false;
  input_file_name = gspyInputArea + gsubArea + TString(option) + ".root";
  output_file_name = gspyOutputArea + gsubArea + "out_" + TString(option)+".root";
  input_file = new TFile(input_file_name, "read");
  if (input_file == NULL) {
    printf(" no input file found\n");
    return;
    }*/
  output_file = new TFile("/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output.root", "recreate");
  fwlite_ChainEvent_ptr = new fwlite::ChainEvent(input_file_names);
  FileReader * reader = 
                   new FileReader(
		   new EventConverter<ReadEvent_llvv>(
		   //new Purge(
		   //new UncertaintiesNode(*/	
		   new BTagger(
		   /*	new Fork(*/
		   new UncertaintiesApplicator(
		   new PileUpCorrector(	  
		   new Selector(
		  /*new HistogramFiller(	*/     
		        	NULL
			            )
				    )
                                    )
			            )
			            )
			            );
  reader -> Run();
  reader -> Report();
  /* output_file -> cd();
  if (mapOfHistogramPools != NULL) mapOfHistogramPools -> Write();
  if (mapOfSelectorHistoPools != NULL)
  {
    mapOfSelectorHistoPools -> Write();
    delete mapOfSelectorHistoPools;
  }
  printf("CentralProcessor::Run() going to delete histogram pool\n");
  delete mapOfHistogramPools;
  output_file -> Close();
  input_file -> Close();
  delete input_file;
  delete output_file;*/
  delete reader;
}

void CentralProcessor::AddHistograms(){
  /* HistogramPlotter * histogram_plotter = new HistogramPlotter();
  vector<TString> run_options;
  run_options . push_back(TString("spy_ww"));
  run_options . push_back(TString("spy_wz"));
  run_options . push_back(TString("spy_zz"));
  histogram_plotter -> AddHistograms(& run_options, "spy_dibosons"); 
  delete histogram_plotter;*/
}

void CentralProcessor::StackHistograms(){
  /* HistogramPlotter * histogram_plotter = new HistogramPlotter();
  histogram_plotter -> StackHistograms("spy_total");
  delete histogram_plotter;*/
}

void CentralProcessor::ProduceTables(){

}

void CentralProcessor::RunInTestMode(){
  /* printf("Central Processor running in test mode\n");
  Parser *parser = new Parser();
  parser -> LoadColors();
  delete parser;
  printf("Test finished\n");*/
}

void CentralProcessor::ConstructJetCorrectionObjects(){
  /* stdEtaResol = new JetResolution(getaResolFileName.Data(),false);
  //stdPhiResol = new JetResolution(gphiResolFileName.Data(),false);
  stdPtResol  = new JetResolution(gptResolFileName.Data(),true);
  jetCorrectionUncertainty = new JetCorrectionUncertainty(*(new JetCorrectorParameters(gjesUncFileName.Data(), "Total")));*/
}

void CentralProcessor::DeconstructJetCorrectionObjects(){
  /* delete stdEtaResol;
  //delete stdPhiResol; 
  delete stdPtResol;  
  delete jetCorrectionUncertainty;*/
}

void CentralProcessor::LoadObjectDescriptors(){
  /*Parser *parser = new Parser();
  object_descriptors = parser -> ParseHistogramSpecifier(gspyObjectSpecifiers);
  delete parser;*/
}

void CentralProcessor::LoadMCDataSampleDescriptors(){
  /* Parser *parser = new Parser();
  MCdatasample_descriptors = parser -> ParseDataSampleDescriptor(gspyMCDataSampleSpecifiers);
  delete parser;*/
}
void CentralProcessor::LoadSelectorHistDescriptors(const char* specifier){
  Parser *parser = new Parser();
  selector_h_descriptors = parser -> ParseHistogramSpecifier(specifier);
  delete parser;
}
void CentralProcessor::LoadDataSampleDescriptors(){
  /* Parser *parser = new Parser();
  datasample_descriptors = parser -> ParseDataSampleDescriptor(gspyDataSampleSpecifiers);
  delete parser;*/
}


void CentralProcessor::StartTApplication() const{
  application . Run(kTRUE);
}

void CentralProcessor::TerminateTApplication() const{
  application.Terminate();
}

void CentralProcessor::CloseRegisters(){
  THStack_pool -> Close();
  delete THStack_pool;
  TGraph_pool -> Close();
  delete TGraph_pool;
  if (TCanvas_pool != NULL){
    TCanvas_pool -> Close();
    delete TCanvas_pool;
  }
  
  data_histo_pool -> Close();
  delete data_histo_pool;
  for (unsigned int opt_ind = 0; opt_ind < MCdatasample_descriptors -> size(); opt_ind++){
    histogram_pool[opt_ind].Close();
    histogram_pool[opt_ind].~HistogramPool();
  }
  free(histogram_pool);
  output_file -> Write();
  output_file -> Close();
  delete output_file;
 
  for (unsigned int opt_ind = 0; opt_ind < MCdatasample_descriptors -> size(); opt_ind++){
    input_file[opt_ind].Close();
    input_file[opt_ind].~TFile();
  }
  free(input_file);
  data_file -> Close();
  delete data_file;
  printf("Got here\n");
}

CentralProcessor::~CentralProcessor(){
  printf("Deconstructing CetralProcessor\n");
}
