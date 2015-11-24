#ifndef _HStructure_CombinedTHStackTH1D_hh
#define _HStructure_CombinedTHStackTH1D_hh
#include "TauAnalysis/interface/HStructure_worker.hh"
#include "TauAnalysis/interface/CombinedTHStackTH1D.hh"
class TLegend;
class HStructure_TH1D; 
class HStructure_THStack;

class HStructure_CombinedTHStackTH1D: public HStructure_worker
{
  //HStructure_TH1D * th1d_structure {NULL};
  //HStructure_THStack * thstack_structure {NULL};
public:
  HStructure_CombinedTHStackTH1D();
  HStructure_CombinedTHStackTH1D(const SampleDescriptor &);
  HStructure_CombinedTHStackTH1D(const HStructure &);
  void * operator new (size_t);
  //virtual void PopulateWorkingElements(const char * = "");
  //virtual void AddChild(HStructure*);
  //virtual void AddChild_TH1D(HStructure_TH1D *);
  //virtual void AddChild_THStack(HStructure_THStack *);
  HStructure_THStack * GetChild_MC() const;
  HStructure_TH1D * GetChild_data() const;
  virtual void FillBottomUp(const char *option);

  TLegend * CreateLegend();
  void Join();
  void Process();
  CombinedTHStackTH1D * Get();
  CombinedTHStackTH1D & operator * ();
  CombinedTHStackTH1D * operator -> ();

  virtual const char* WhoAmI() const;
  virtual ~HStructure_CombinedTHStackTH1D();
};

#endif
