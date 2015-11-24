#ifndef _HStructure_TH1D_hh
#define _HStructure_TH1D_hh
#include "TH1D.h"
#include "CERN_RTU/TauAnalysis/interface/HStructure_worker.hh"

using namespace std;

class HStructure_TH1D: public HStructure_worker
{
protected:
  static unsigned int TH1D_inst;
  unsigned int histID;
public:
  //using HStructure_worker::HStructure_worker;
  
  HStructure_TH1D();
  HStructure_TH1D(const HStructure &);
  HStructure_TH1D(const SampleDescriptor &);

  void * operator new(size_t);
  TH1D & operator *();
  TH1D * operator -> ();
  operator TH1D*();
  TH1D * Get();
  virtual void PopulateWorkingElements(const char * = "");
  virtual void FillBottomUp(const char * = "");
  virtual const char* WhoAmI() const;
  virtual ~HStructure_TH1D();
  unsigned int GetHistID() const;
  void Stamp();
  void RemoveStamp();
  void FixStamp();
  
};

#endif
