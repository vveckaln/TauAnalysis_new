#ifndef _HStructure_hh
#define _HStructure_hh
#include "CERN_RTU/TauAnalysis/interface/HistogramDescriptor.hh"

#include <cstddef>
#include <vector>
using namespace std;
class HStructure_worker;
class HStructure_TFile;
//class HStructure_TFile::iterator;
enum EStatusBits{pCanDelete, kOpenForInput, kOpenForOutput, kIsFilled, kIsData, kIsManager, kIsStamped, kIsValid};
class HStructure: public SampleDescriptor
{
  static unsigned int unique_id;
  friend class Parser;
protected:
  void IterateDown(void (HStructure::*func)(const char *), const char * = "");
  void IterateDown(void (HStructure::*func)(const char *) const, const char * = "") const;
  unsigned char StatusBits {0};
  
  vector<HStructure *> children;
  HStructure * parent {NULL};
public:
  class iterator
  {
    friend class HStructure; 
    friend class HStructure_TFile;
  protected:
    static const HStructure * const END;
    static const HStructure * const ITER;
    HStructure * generator {NULL};
    HStructure * to {NULL};
    HStructure *& GetRefGenerator(HStructure::iterator &);
    HStructure *& GetRefTo(HStructure::iterator &);
    friend HStructure *& GetRefGenerator(HStructure::iterator &);
    friend HStructure *& GetRefTo(HStructure::iterator &);

  public:
    iterator();
    iterator(HStructure * to);
    HStructure * operator -> ();
    iterator operator ++(int);
    iterator operator ++();

    iterator operator -- ();
    iterator & increment(const char * = "");
    iterator & decrement(const char * = "");
    bool operator == (const HStructure *);
    bool operator != (const HStructure *);
    bool operator != (const HStructure::iterator &);
    iterator & operator = (HStructure *);
    HStructure & operator *();
  };
  
  void * operator new (size_t);
  void * operator new (size_t, const SampleDescriptor &);

  unsigned char GetStatusBits() const;
  void SetStatusBits(const unsigned char);
  void something();
  HStructure::iterator begin(const char * = "") const;
  HStructure::iterator end(const char * = "") const;
  HStructure * Apex();
  HStructure * Last();

  HStructure * GetNextChild(const HStructure *) const;
  HStructure * GetNextSibling() const;
  HStructure * Next(const char * = "") const;

  HStructure * GetPreviousChild(const HStructure *) const;
  HStructure * GetPreviousSibling() const;
  HStructure * Previous(const char * = "") const;

  HStructure * GetHStructure(const char *) const;
  void SetParent(HStructure *);
  HStructure * Parent() const;
  vector<HStructure *> & GetChildren() ;
  const vector<HStructure *> & GetChildren() const;

  void lsSample() const;
  HStructure();
  HStructure(const SampleDescriptor &);
  HStructure * Clone(const char * = "");
  
  virtual void AddChild(HStructure *);
  bool TestBit(unsigned char) const;
  void SetBit(unsigned char, bool, const char* = "");
  virtual void ls(const char * = "") const;
  void ls_bckw(const char * = "");
  virtual void test(const char * = "") ;
  virtual void Write(const char * = "");
  template<typename hstructure>
  HStructure * ConvertToHStructure(const char* = "");
  void OrderChildren();
  void Delete(const char *);
  virtual const char* WhoAmI() const;
  virtual ~HStructure();
  
};
void printb(const unsigned numb);

template<typename hstructure>
HStructure * HStructure::ConvertToHStructure(const char* option)
{
  const TString comp = option;
  HStructure * ret;
  if (comp != "descendants")
    {
      printf("Before cloning children size %lu\n", GetChildren().size());

      ret = new hstructure(*this);
      delete this;
      printf("After cloning children size %lu\n", ret -> GetChildren().size());
    }
  else 
    {
      ret = this;
    }
  for (unsigned char ind = 0; ind < ret -> children.size(); ind ++)
    {
      if (comp == "all" or comp == "descendants")
	{
	  printf("converting\n");
	  ret -> children[ind] -> ls();
	  ret -> children[ind] = ret -> children[ind] -> ConvertToHStructure<hstructure>("all");
	}
      ret -> children[ind] -> parent = ret;
    }
  return ret;
}

bool TestOption(const char *, const char *);
inline TString AddOptions(const char*, const char*);

#endif
