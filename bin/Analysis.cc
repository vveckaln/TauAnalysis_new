//#include <boost/shared_ptr.hpp>

#include "LIP/TauAnalysis/interface/gConfiguration.hh"
#include "LIP/TauAnalysis/interface/CentralProcessor.hh"
#include "TSystem.h"

using namespace std;
int main(int argc, char* argv[])
{
  fprintf(stderr, "running Analysis\n");
  if (string(argv[1]).compare(string("none")) != 0)
    gConfiguration -> SetConfiguration(argv[1]);
  CentralProcessor * central_processor = new CentralProcessor();
  central_processor -> LoadSelectorHistDescriptors(gwork_directory + "/data/histogram_specifiers/spec_selector_histograms.xml");
  TString option = TString(argv[2]);
  if (option == "process")
    central_processor -> Process("");
  if (option == "hadd")
    central_processor -> AddHistograms();
  /*central_processor -> StartTApplication();
  central_processor -> TerminateTApplication();*/
  if (option == "SumData")
    central_processor -> SumData();
  if (option == "produce_total")
    central_processor -> ProduceTotal();
  if (option == "tau_fakes")
    central_processor -> ProduceTauFakes();
  central_processor -> CloseRegisters();
  delete central_processor;
}
