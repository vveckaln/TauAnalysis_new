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
  void SumData() const;
  void ProduceTotal() const;
  void SetEnvironment() const;
  void SetEnvironment_TTbarMC() const;
  void SetEnvironment_DY() const;
  void SetEnvironment_tW() const;
  void OpenOutputFiles() const;
  void FormatHistograms() const;
  void ProduceTauFakes() const;
  void CloseRegisters();
  virtual ~CentralProcessor();

};
#endif
