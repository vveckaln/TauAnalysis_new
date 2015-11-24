#ifndef _HStructure_worker_hh
#define _HStructure_worker_hh
#include "CERN_RTU/TauAnalysis/interface/HStructure.hh"
#include "TObject.h"
using namespace std;

class HStructure_worker: public HStructure
{
protected:
  TObject * worker {NULL};
public:
  HStructure_worker();
  HStructure_worker(const HStructure &);
  HStructure_worker(const SampleDescriptor &);
  class iterator: public HStructure::iterator
  {
    friend class HStructure::iterator;
  public:
    iterator(HStructure * to);
    iterator(HStructure::iterator &&);
    HStructure_worker * operator -> ();
    HStructure_worker & operator *();
  };
  void * operator new (size_t);
  TObject *& GetRef();
  TObject * GetPtr() const;
  HStructure_worker * GetHStructure(const char *, const char * = "") const;
  virtual void AddChild(HStructure *);
  virtual void PopulateWorkingElements(const char * = "");
  virtual void LoadObjects(const char * = "");
  virtual void FillBottomUp(const char * = "");
  virtual void ls(const char * = "") const;
  virtual void test(const char * = "");
  virtual void Write(const char * = "");
  virtual const char* WhoAmI() const;
  virtual ~HStructure_worker();
};

#endif
