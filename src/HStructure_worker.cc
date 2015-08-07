#include "LIP/TauAnalysis/interface/HStructure_worker.hh"
#include "LIP/TauAnalysis/interface/HStructure_TH1D.hh"
#include "LIP/TauAnalysis/interface/HStructure_THStack.hh"
#include "LIP/TauAnalysis/interface/HStructure_CombinedTHStackTH1D.hh"

#include "LIP/TauAnalysis/interface/HStructure_TFile.hh"
#include "LIP/TauAnalysis/interface/Utilities.hh"

#include "LIP/TauAnalysis/interface/Register.hh"
using namespace utilities;
HStructure_worker::HStructure_worker()
{
}

HStructure_worker::HStructure_worker(const HStructure & structure): HStructure(structure)
{
}

HStructure_worker::HStructure_worker(const SampleDescriptor & other): HStructure(other)
{
}

HStructure_worker::iterator::iterator(HStructure::iterator&& other)
{
  to = GetRefTo(other);
  GetRefTo(other) = NULL;
  generator = GetRefGenerator(other);
  GetRefGenerator(other) = NULL;
}

HStructure_worker * HStructure_worker::iterator::operator -> ()
{
  return (HStructure_worker*) to;
}

HStructure_worker & HStructure_worker::iterator::operator * ()
{
  return *(HStructure_worker*) to;
}

void * HStructure_worker::operator new (size_t size)
{
  return ::new HStructure_worker;
}

TObject *& HStructure_worker::GetRef()
{
  return worker;
}

TObject * HStructure_worker::GetPtr() const
{
  return worker;
}

HStructure_worker * HStructure_worker::GetHStructure(const char * sample_name, const char * worker_name) const
{
  if (TString(worker_name) == "")
    {
      return (HStructure_worker*)HStructure::GetHStructure(sample_name);
    }
  const HStructure_worker * ret = this;
  bool found = false; 
  while(not found and ret)
    {
      
      found = TString(ret -> GetName()) == TString(sample_name) and TString(ret -> GetPtr() -> GetName()).Contains(worker_name);
      if (not found) 
	ret = (const HStructure_worker*)ret -> Next();
    }
  
  return const_cast<HStructure_worker*>(ret);
}

void HStructure_worker::AddChild(HStructure * structure)
{
  this -> HStructure::AddChild(structure);
}

void HStructure_worker::PopulateWorkingElements(const char * option)
{
  if (TString(option) == "iter") goto cont; 
  for (HStructure::iterator it = begin(option); it != end(option); it.increment(option))
    {
      //((HStructure_worker*)it) -> PopulateWorkingElement("iter");
    }
  return;
  cont:
  return;
}


void HStructure_worker::LoadObjects(const char * option)
{
  //IterateDown(&HierarchicalStructure_worker::LoadObjects, option);
}
 
void HStructure_worker::FillBottomUp(const char * option)
{
  //if (TString(option) == "iter") goto cont;
  for (HStructure_worker::iterator it = --end(option); it != --begin(option); it.decrement(option))
    {
      it -> lsSample();
      it -> FillBottomUp("iter");
      it -> SetBit(kIsFilled, true);
    } 
  //cont:
}
  
void HStructure_worker::ls(const char * option) const
{
  HStructure::ls();
  printf(" Is Filled %s %p;\n", TestBit(kIsFilled) ? "true" : "false", worker); 
  if (worker)
    printf("worker %s\n", worker -> GetName());
  if (TString(option) == "all" or TString(option) == "descendants")
    {
      if (children.size() > 0)
	printf("listing children and structures below each child\n");
      else
	printf("no children\n");
      IterateDown(&HStructure::ls, option);
    }
}

void HStructure_worker::test(const char * option)
{
  HStructure::test(option);
  if (not TestOption(option, "iter")) return;
  printf(" Is Filled %s;\n", to_char(TestBit(kIsFilled))); 
  if (worker)
    printf("worker %s\n", worker -> GetName());
  else
    printf("no worker\n");
}

void HStructure_worker::Write(const char * option)
{
  for (HStructure_worker::iterator it = begin(option); it != end(option); it.increment(option))
    {
      if (not it -> GetPtr()) continue;
      if (not cpregister::active_HStructure_TFile -> GetHStructure(it -> GetName()) -> TestBit(kOpenForOutput))
	{
	  
	  continue;
	}
      TFile * file = ((HStructure_TFile*)cpregister::active_HStructure_TFile -> GetHStructure(it -> GetName())) -> GetFile();
      file -> cd();
      //printf("%s\n", it -> WhoAmI());
      if (TString(it -> WhoAmI()) == "HStructure_TH1D")
	{
	  ((HStructure_TH1D*)&*it) -> RemoveStamp();
	  it -> GetPtr() -> Write();
	  ((HStructure_TH1D*)&*it) -> Stamp();
	  	  

	 
	    
	}
      else if (TString(it -> WhoAmI()) == "HStructure_CombinedTHStackTH1D")
	{
	  HStructure_CombinedTHStackTH1D * str = ((HStructure_CombinedTHStackTH1D*)&*it);
	  //printf("Writing combined%s\n", str -> GetChild_data() -> GetName());
	  str -> GetChild_data() -> RemoveStamp();
	  //printf("After removing stamp %s\n", str -> GetChild_data() -> GetName());
	  it -> GetPtr() -> Write();
	  str -> GetChild_data() -> Stamp();
	  // printf("After restamping %s\n", str -> GetChild_data() -> GetName());

	  //getchar();
	    
	}
      else
	{
	  //printf("writing %s\n", it -> WhoAmI());
	  it -> GetPtr() -> Write();
	}
      
    }
}



const char* HStructure_worker::WhoAmI() const
{
  return "HStructure_worker";
}

HStructure_worker::~HStructure_worker()
{

}
