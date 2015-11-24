#ifndef _HStructure_TFile_hh
#define _HStructure_TFile_hh
#include "TauAnalysis/interface/HStructure.hh"
#include "TFile.h"
class HStructure_work;
class HStructure_TFile: public HStructure
{
protected:
  TFile * file {NULL};
public:
  HStructure_TFile();
  HStructure_TFile(const HStructure &);
  class iterator: public HStructure::iterator
  {
    friend class HStructure::iterator;
  public:
    iterator(HStructure * to);
    iterator(HStructure::iterator &&);
    HStructure_TFile * operator -> ();
    HStructure_TFile & operator *();
  };
  void * operator new (size_t);
  void * operator new (size_t, const SampleDescriptor &);
  TFile & operator * ();
  TFile * operator -> ();
  TFile * GetFile();
  TFile *& GetRef();
  HStructure_TFile & operator = (TFile *);
  void cd();
  static HStructure_TFile* Open(const char* name, Option_t* option = "");
  void OpenForInput(const char * = "", const char * = "hh");
  void test2(const char * = "", const char * = "hh");
 
  void OpenForOutput(const char * = "", const char * directory = "");
  HStructure_worker * Get(const char*);
  HStructure_worker * Get1(const char*);

  HStructure_worker * GenerateWorker(const HistogramDescriptor &);
  void Close(const char * = "");
  virtual void test(const char* = "");
  //virtual void ls(const char * = "") const;
  const char* WhoAmI() const;
  virtual ~HStructure_TFile();
};

#endif
