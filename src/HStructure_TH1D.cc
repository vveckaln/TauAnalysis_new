#include "CERN_RTU/TauAnalysis/interface/HStructure_TH1D.hh"
//#include "CERN_RTU/TauAnalysis/interface/Table.h"

#include "CERN_RTU/TauAnalysis/interface/Register.hh"

unsigned int HStructure_TH1D::TH1D_inst = 0;

HStructure_TH1D::HStructure_TH1D()
{
  histID = TH1D_inst;
  TH1D_inst ++;
  
}

HStructure_TH1D::HStructure_TH1D(const  HStructure &structure) : HStructure_worker(structure)
{
  histID = TH1D_inst;
  TH1D_inst ++;
  
}

HStructure_TH1D::HStructure_TH1D(const SampleDescriptor &other) : HStructure_worker(other)
{
  histID = TH1D_inst;
  TH1D_inst++;
  
}

void * HStructure_TH1D::operator new (size_t size)
{
  return ::operator new(size);
}

void HStructure_TH1D::PopulateWorkingElements(const char * option)
{
  
  //IterateDown(&HierarchicalStructure_worker::PopulateWorkingElements, option);
}

void HStructure_TH1D::FillBottomUp(const char *option)
{
  try
    {
      HStructure_worker::FillBottomUp(option);
      if (TString(option) != "iter") return;
      if(TestBit(kIsFilled)) 
	return;
      SetBit(kIsStamped, ((HStructure_TH1D*)GetChildren().front()) -> TestBit(kIsStamped));
      unsigned char invalid_children(0), empty_children(0);
      for (unsigned char child_ind = 0; child_ind < GetChildren().size(); child_ind ++)
	{

	  if (not GetChildren()[child_ind] -> TestBit(kIsValid)) invalid_children ++; 
	  if (not ((HStructure_TH1D*)GetChildren()[child_ind]) -> Get()) empty_children ++;
	}
      for (unsigned char child_ind = 0; child_ind < GetChildren().size(); child_ind ++)
	{

	 
	  if (GetChildren()[child_ind] -> TestBit(kIsValid) and ((HStructure_TH1D*)GetChildren()[child_ind]) -> Get())
	    {
	      GetRef() = (TH1D*)(((HStructure_TH1D*)GetChildren()[child_ind]) -> Get() -> Clone());
	      break;
	    }
	  if (child_ind == GetChildren().size() - 1)
	    {
	      printf("no valid children encountered\n");
	      throw "no valid children encountered\n";
	    }
	}
      printf("name %s, children %lu, invalid %u, empty %u\n", GetName(), GetChildren().size(), invalid_children, empty_children);
      FixStamp();
      Get() -> Reset();
      for (unsigned char child_ind = 0; child_ind < GetChildren().size(); child_ind ++)
	{
	  if (children[child_ind] -> TestBit(kIsValid) and ((HStructure_TH1D*)children[child_ind]) -> Get())
	    Get() -> Add(*(HStructure_TH1D*)children[child_ind]);
	}
      Get() -> SetFillColor(fill_color);
 
    } catch (const char* e)
    {
      cerr<<"exception caught "<< e <<"\n";
    }
}

const char * HStructure_TH1D::WhoAmI() const
{
  return "HStructure_TH1D";
}

TH1D * HStructure_TH1D::Get()
{
  return (TH1D*)worker;
}

HStructure_TH1D::operator TH1D*()
{
  return (TH1D*) worker;
}

unsigned int HStructure_TH1D::GetHistID() const
{
  return histID;
}

void HStructure_TH1D::Stamp()
{
  if (TestBit(kIsStamped) or not Get()) return;
  
  char name[128];
  sprintf(name, "%s_%u\n", Get() -> GetName(), GetHistID());
  Get() -> SetName(name);
  SetBit(kIsStamped, true);
}

void HStructure_TH1D::RemoveStamp()
{
  if (not TestBit(kIsStamped) or not Get()) return;
  const char * name = Get() -> GetName();
  
  const char *end;
  for (end = name; *end != '\0'; end++);
  do{ end--;}while (*end !='_');
  char new_name[128];
  const char  *indicator; unsigned char ind = 0;
  for (indicator = name; indicator != end; ind ++, indicator ++)
    {
      new_name[ind] = *indicator;
    }
  new_name[ind] = '\0';
  Get() -> SetName(new_name);
  SetBit(kIsStamped, "false");
}

void HStructure_TH1D::FixStamp()
{
  RemoveStamp();
  Stamp();
}

HStructure_TH1D::~HStructure_TH1D()
{

}
