#ifndef _HStructure_THStack_hh
#define _HStructure_THStack_hh
#include "CERN_RTU/TauAnalysis/interface/HStructure_worker.hh"
#include "THStack.h"
#include "TLegend.h"

using namespace std;

class HStructure_THStack: public HStructure_worker
{

public:
  HStructure_THStack();
  HStructure_THStack(const HStructure &);
  HStructure_THStack(const SampleDescriptor &);

  void * operator new (size_t);
  TLegend* GetLegend() const;
  virtual void PopulateWorkingElements(const char * = "");
  virtual void FillBottomUp(const char * = "");
  THStack * Get() const;
  
  //THStack *& GetRef();
  THStack * operator -> ();
  THStack & operator * ();
  virtual const char* WhoAmI() const;
  virtual ~HStructure_THStack();
};
#endif
