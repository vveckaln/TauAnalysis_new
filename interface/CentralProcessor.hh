#ifndef _CentralProcessor_hh
#define _CentralProcessor_hh
#include "TFile.h"
#include "TString.h"

class CentralProcessor
{
public:
  CentralProcessor();
  void Process(const char *);
  //void Process(const char * option = "add_histograms"){};
  void AddHistograms();
  void StackHistograms();
  void ProduceTables();
  void RunInTestMode();
  void ConstructJetCorrectionObjects();
  void DeconstructJetCorrectionObjects();
  void LoadObjectDescriptors();
  void LoadMCDataSampleDescriptors();
  void LoadDataSampleDescriptors();
  void LoadSelectorHistDescriptors(const char*);
  void StartTApplication() const;
  void TerminateTApplication() const;
  void CloseRegisters();
  virtual ~CentralProcessor();

};
#endif
