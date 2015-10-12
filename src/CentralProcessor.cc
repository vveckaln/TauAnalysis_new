
#include "LIP/TauAnalysis/interface/CentralProcessor.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"

#include "LIP/TauAnalysis/interface/HistogramPlotter.hh"
#include "LIP/TauAnalysis/interface/ReadEvent.hh"
#include "LIP/TauAnalysis/interface/FileReader.hh"
#include "LIP/TauAnalysis/interface/SamplesCatalogue.hh"

#include "LIP/TauAnalysis/interface/Preselector_Leptons.hh"
#include "LIP/TauAnalysis/interface/Preselector_Jets.hh"
#include "LIP/TauAnalysis/interface/Preselector_MET.hh"
#include "LIP/TauAnalysis/interface/Preselector_Taus.hh"
#include "LIP/TauAnalysis/interface/Preselector_OS.hh"
#include "LIP/TauAnalysis/interface/Fork_Subsample.hh"

/*#include "LIP/TauAnalysis/interface/ReadEvent_llvv.hh"*/
#include "LIP/TauAnalysis/interface/BTagger.hh"
//#include "LIP/TauAnalysis/interface/Selector.hh"*/
#include "LIP/TauAnalysis/interface/ChannelGate.hh"

/*#include "LIP/TauAnalysis/interface/KINbHandler.hh"*/
#include "LIP/TauAnalysis/interface/Fork.hh"
/*#include "LIP/TauAnalysis/interface/Purge.hh"*/

//#include "LIP/TauAnalysis/interface/HistogramFiller.hh"
/*  #include "LIP/TauAnalysis/interface/UncertaintiesNode.hh"*/
#include "LIP/TauAnalysis/interface/PileUpCorrector.hh"
#include "LIP/TauAnalysis/interface/HStructure.hh"
#include "LIP/TauAnalysis/interface/HStructure_THStack.hh"
#include "LIP/TauAnalysis/interface/HStructure_TH1D.hh"
#include "LIP/TauAnalysis/interface/HStructure_CombinedTHStackTH1D.hh"
#include "LIP/TauAnalysis/interface/HStructure_TFile.hh"

#include "LIP/TauAnalysis/interface/CombinedTHStackTH1D.hh"

//#include "LIP/TauAnalysis/interface/UncertaintiesApplicator.hh"
#include "LIP/TauAnalysis/interface/MuScleFitCorrectorApplicator.hh"

#include "LIP/TauAnalysis/interface/Register.hh"
#include "LIP/TauAnalysis/interface/Parser.hh"
#include "TLegend.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "THStack.h"

using namespace cpregister;
using namespace gVariables;

CentralProcessor::CentralProcessor()
{
  //  gc_gConfiguration = new GlobalConfiguration();
  
}

void CentralProcessor::SetEnvironment() const
{
  number_of_samples = & generic_samples_count;
  samples_names     = generic_samples_names;
  IsGeneric         = true;
  IsTTbarMC         = gdtag.Contains("TTJets") or gdtag.Contains("_TT_");
  IsDY              = gdtag.Contains("DY");
  IstW              = gdtag.Contains("tW");
  IsWJets           = gdtag.Contains("WJets");
  if (IsTTbarMC) SetEnvironment_TTbarMC();
  if (IsDY)      SetEnvironment_DY();
  if (IstW)      SetEnvironment_tW();
}

void CentralProcessor::Process(const char* option)
{
  for (size_t ind = 0; ind < input_file_names.size(); ind++)
    printf("file %lu %s\n", ind, input_file_names[ind].c_str());
  //getchar();
  //  fwlite_ChainEvent_ptr = new fwlite::ChainEvent(input_file_names);
  
  
  //output_file_name  = gOutputDirectoryName + "/output_files/output_event_analysis/" + TString(gSystem -> BaseName(input_file_name)) . 
  //ReplaceAll(".root", "") + "_out.root";
  SetEnvironment();
  OpenOutputFiles();

   IsSingleMuPD     = gIsData and gdtag.Contains("SingleMu");
  
  FileReader * reader = 
    new FileReader(
    new MuScleFitCorrectorApplicator(
    new Preselector_Leptons(
    new Preselector_Taus(
    new Preselector_Jets(
								//new Purge(
								//new UncertaintiesNode(*/
								// new Fork(
								//new UncertaintiesApplicator(				       
    new ChannelGate(
    new Fork_Subsample(
		       new PileUpCorrector(	  
    new Preselector_MET(
    new BTagger(	     
    
			 new Preselector_OS(NULL)))))))))));
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
  printf("Going to write\n");
  hstruct_worker -> Write("all");
  
  active_HStructure_TFile -> Close("all");
}

void CentralProcessor::AddHistograms()
{
  SetEnvironment();
  printf("gfile_split %u\n", gfile_split);
  input_file_name = gOutputDirectoryName + "/output_files/event_analysis/" + gdtag;
  printf("input_file_name stub %s\n", input_file_name.Data());
  for (unsigned short segment_ind = 0; segment_ind < *number_of_samples; segment_ind ++)
    {
      number_active_sample = segment_ind;
      HStructure_TFile * files_mother = new HStructure_TFile;
      files_mother -> cd();
      for (unsigned short file_ind = 0; file_ind < gfile_split; file_ind ++)
	{
	  TString name;
	  if (number_of_samples == & generic_samples_count)
	    {
		name = input_file_name + "_" + TString(to_string(file_ind)) + "_out.root";
	    }
	  else
	    {
		name = input_file_name + "_" + samples_names[segment_ind] + "_" + TString(to_string(file_ind)) + "_out.root";
	    }
	  //printf("%s %u\n", samples_names[segment_ind].Data(), file_ind);
	  //printf("input from file %s\n", name.Data());
	  HStructure_TFile *file_struct = HStructure_TFile::Open(name, "READ");
	  
	  if (file_struct)
	    files_mother -> AddChild(file_struct);
	}
      //files_mother -> test("all");
      
    
      //getchar();
      if (samples_names[segment_ind] != "generic_name") 
	  output_file_name = gOutputDirectoryName + "/output_files/hadd/" + gdtag + "_" + samples_names[segment_ind] + "_TOTAL_out.root";
      else
	  output_file_name = gOutputDirectoryName + "/output_files/hadd/" + gdtag + "_TOTAL_out.root";
      output_file = new TFile(output_file_name, "recreate");
      printf("output_file_name %s\n", output_file_name.Data());
      //getchar();
      HistogramPlotter * histogram_plotter = new HistogramPlotter();

      histogram_plotter -> AddHistograms(); 
      delete histogram_plotter;
      output_file -> Close();
  }
}

void CentralProcessor::StackHistograms()
{
  /* HistogramPlotter * histogram_plotter = new HistogramPlotter();
  histogram_plotter -> StackHistograms("spy_total");
  delete histogram_plotter;*/
}

void CentralProcessor::ProduceTables()
{

}

void CentralProcessor::RunInTestMode()
{
  /* printf("Central Processor running in test mode\n");
  Parser *parser = new Parser();
  parser -> LoadColors();
  delete parser;
  printf("Test finished\n");*/
}

void CentralProcessor::ConstructJetCorrectionObjects()
{
  /* stdEtaResol = new JetResolution(getaResolFileName.Data(),false);
  //stdPhiResol = new JetResolution(gphiResolFileName.Data(),false);
  stdPtResol  = new JetResolution(gptResolFileName.Data(),true);
  jetCorrectionUncertainty = new JetCorrectionUncertainty(*(new JetCorrectorParameters(gjesUncFileName.Data(), "Total")));*/
}

void CentralProcessor::DeconstructJetCorrectionObjects()
{
  /* delete stdEtaResol;
  //delete stdPhiResol; 
  delete stdPtResol;  
  delete jetCorrectionUncertainty;*/
}

void CentralProcessor::LoadObjectDescriptors()
{
  /*Parser *parser = new Parser();
  object_descriptors = parser -> ParseHistogramSpecifier(gspyObjectSpecifiers);
  delete parser;*/
}

void CentralProcessor::LoadMCDataSampleDescriptors()
{
  /* Parser *parser = new Parser();
  MCdatasample_descriptors = parser -> ParseDataSampleDescriptor(gspyMCDataSampleSpecifiers);
  delete parser;*/
}
void CentralProcessor::LoadSelectorHistDescriptors(const char* specifier)
{
  Parser *parser = new Parser();
  selector_h_descriptors = parser -> ParseHistogramSpecifier(specifier);
  delete parser;
}
void CentralProcessor::LoadDataSampleDescriptors()
{
  /* Parser *parser = new Parser();
  datasample_descriptors = parser -> ParseDataSampleDescriptor(gspyDataSampleSpecifiers);
  delete parser;*/
}

void CentralProcessor::StartTApplication() const
{
  application . Run(kTRUE);
}

void CentralProcessor::TerminateTApplication() const
{
  application.Terminate();
}

void CentralProcessor::SumData() const
{
  output_file_name = gOutputDirectoryName + "/output_files/output_hadd/" + "Data8TeV_SingleMu2012_TOTAL_out.root";
  output_file = new TFile(output_file_name, "recreate");
  
  
  HistogramPlotter * histogram_plotter = new HistogramPlotter;
  histogram_plotter -> SumData();
  delete histogram_plotter;
}

void CentralProcessor::ProduceTotal() const
{
  Parser parser;
  HStructure * structure = parser . CreateHierarchicalStructure(gwork_directory + "/data/histogram_specifiers/spec_samples.xml");
  HStructure * structure_data = parser . CreateHierarchicalStructure(gwork_directory + "/data/histogram_specifiers/spec_data.xml");
  vector<HistogramDescriptor> * hdescr = parser.ParseHistogramSpecifier(gwork_directory + "/data/histogram_specifiers/spec_selector_histograms.xml");
  const unsigned char size = hdescr -> size();
  for (unsigned char ind = 0; ind < hdescr -> size(); ind ++)
    {
      hdescr -> at(ind) . ls();
    }
  HStructure_TFile * structure_files = (HStructure_TFile*)structure -> ConvertToHStructure<HStructure_TFile>("all");
  structure_files -> OrderChildren();
  HStructure_TFile * structure_files_data = (HStructure_TFile*)structure_data -> ConvertToHStructure<HStructure_TFile>("all");
  structure_files_data -> SetBit(kIsData, "true", "all");
  HStructure_TFile * files_mother = new HStructure_TFile;
  files_mother -> SetName("13TeV");
  files_mother -> SetTitle("13TeV");
  files_mother -> AddChild(structure_files);
  files_mother -> AddChild(structure_files_data);
  files_mother -> OpenForInput("all", gOutputDirectoryName + "/output_files/hadd");
  files_mother -> OpenForOutput("all", gOutputDirectoryName + "/output_files/total_new");
  printf("Going to list files mother\n"); getchar();
  files_mother -> test("all"); getchar();
  files_mother -> cd();
  printf("Extracting from file\n");
  HStructure_worker * manager = new HStructure_worker;
  HStructure_worker * worker[size];
  for (unsigned char ind = 0; ind < size; ind ++)
    {
      worker[ind] = files_mother -> Get(hdescr -> at(ind).histogram_name);
      manager -> AddChild(worker[ind]);
    }
  
   manager -> test("all");
   
  
  printf("Going to fill\n");
  manager -> FillBottomUp("descendants");
printf("List children\n");
  manager -> test("all");
  getchar();
  //worker -> test("all");
  /*worker -> Join();
    worker -> Process();*/
  manager -> Write("descendants");
  files_mother -> Close();
  
}

void CentralProcessor::OpenOutputFiles() const
{
  HStructure_TFile *files_mother = new HStructure_TFile;
  files_mother -> ID = "1";
  files_mother -> cd();
  for (unsigned char sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)
    {
      if (number_of_samples == &generic_samples_count)
	output_file_name = gOutputDirectoryName 
	  + "/output_files/event_analysis/" 
	  + gdtag + "_" + TString(to_string(gsegment)) 
	  + "_out.root";
      else
	{
	    output_file_name  = gOutputDirectoryName 
	      + "/output_files/event_analysis/" 
	      + gdtag 
	      + "_" + samples_names[sample_ind] + "_" +  TString(to_string(gsegment))
	      + "_out.root";
	}
      HStructure_TFile *str_f = HStructure_TFile::Open(output_file_name, "RECREATE");
      str_f -> SetName(samples_names[sample_ind]);
      files_mother-> AddChild(str_f);
    }  
  //output_file_pool = new TFilePool(output_file_names, "RECREATE");
  files_mother -> SetBit(kOpenForOutput, true, "children");
  //files_mother -> test("children");  
  Parser parser;
  vector<HistogramDescriptor> * hdescr = parser.ParseHistogramSpecifier(gwork_directory + "/data/histogram_specifiers/spec_selector_histograms.xml");
  const unsigned char size = hdescr -> size();
  HStructure_worker * worker_mother = new HStructure_worker;
  for (unsigned char ind = 0; ind < size; ind ++)
    {
      worker_mother -> AddChild(files_mother -> GenerateWorker(hdescr -> at(ind)));
    }
  printf("LISTING WORKER\n");
  hstruct_worker = worker_mother;

  const char *Xaxis_labels[5] = 
    {
      "1 lept, #geq 3 jets", 
      "E^{miss}_{T}", 
      "#geq 1btag", 
      "1#tau", 
      "OS"
    };


  for (unsigned short sample_ind = 0; sample_ind < *number_of_samples; sample_ind ++)
    {
      printf("%s\n", samples_names[sample_ind].Data());
      HStructure_TH1D * test = (HStructure_TH1D*)hstruct_worker -> GetHStructure(samples_names[sample_ind], "numb_events_selection_stagesSELECTOR_BASE");
      printf("test %p\n", test);
      TH1D * h = (TH1D*)hstruct_worker -> GetHStructure(samples_names[sample_ind], "numb_events_selection_stagesSELECTOR_BASE") -> GetRef(); 
       TAxis *xaxis = h -> GetXaxis();
      
      for (int binind = 1; binind <= xaxis -> GetNbins(); binind ++)
	{
	  xaxis -> SetBinLabel(binind, Xaxis_labels[binind - 1]);
	}
    }
}

void CentralProcessor::SetEnvironment_TTbarMC() const
{
  number_of_samples = & ttbar_samples_count;
  samples_names     = ttbar_samples_names;
  IsGeneric         = false;
}

void CentralProcessor::SetEnvironment_DY() const
{
  number_of_samples = & DY_samples_count;
  samples_names     = DY_samples_names;
  IsGeneric         = false;
}

void CentralProcessor::SetEnvironment_tW() const
{
  number_of_samples = & ttbar_samples_count;
  samples_names     = ttbar_samples_names;
  IsGeneric         = false;
}

void CentralProcessor::ProduceTauFakes() const
{
  Parser parser;
  HStructure * structure = parser . CreateHierarchicalStructure(gwork_directory + "/data/histogram_specifiers/spec_samples_taufakes.xml");
  vector<HistogramDescriptor> * hdescr = parser.ParseHistogramSpecifier(gwork_directory + "/data/histogram_specifiers/spec_selector_histograms.xml");
  HStructure_TFile * structure_files = (HStructure_TFile*)structure -> ConvertToHStructure<HStructure_TFile>("all");
  printf("open for input\n");
  structure_files -> OpenForInput("all", gOutputDirectoryName + "/output_files/tau_fakes_input");
  printf("open for output\n"); getchar();
  structure_files -> OpenForOutput("all", gOutputDirectoryName + "/output_files/tau_fakes");
  structure_files -> test("all"); getchar();
  structure_files -> cd();
  printf("Extracting from file\n");
  HStructure_worker * manager = new HStructure_worker;
    const unsigned char size = hdescr -> size();

  HStructure_worker * worker[size];
  for (unsigned char ind = 0; ind < size; ind ++)
    {
      worker[ind] = structure_files -> Get1(hdescr -> at(ind).histogram_name);
      manager -> AddChild(worker[ind]);
    }
  
  manager -> test("all");
  manager -> FillBottomUp("descendants");
  manager -> Write("descendants");
  structure_files -> Close();
}

void CentralProcessor::CloseRegisters()
{
  /*THStack_pool -> Close();
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
  printf("Got here\n");*/
  
  if (input_file != NULL) input_file -> Close();
  if (output_file != NULL) output_file -> Close();
}

CentralProcessor::~CentralProcessor()
{
  printf("Deconstructing CetralProcessor\n");
}
