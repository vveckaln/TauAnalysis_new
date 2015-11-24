#include "TauAnalysis/interface/HStructure_THStack.hh"
#include "TauAnalysis/interface/HStructure_TH1D.hh"
#include "TList.h"

#include "TauAnalysis/interface/Table.h"

HStructure_THStack::HStructure_THStack()
{
}

HStructure_THStack::HStructure_THStack(const HStructure & structure):
  HStructure_worker(structure)
{
}

HStructure_THStack::HStructure_THStack(const SampleDescriptor & other):
  HStructure_worker(other)
{
}

void * HStructure_THStack::operator new (size_t size)
{
  return ::new HStructure_THStack;
}

void HStructure_THStack::PopulateWorkingElements(const char * option)
{
  /* if(TString(option) == "all")
     IterateDown(&HierarchicalStructure::PopulateWorkingElements, option);*/
}

void HStructure_THStack::FillBottomUp(const char * option)
{
  HStructure_worker::FillBottomUp(option);
  if (TString(option) != "iter") return;
  if(TestBit(kIsFilled)) 
    return;
  ((HStructure_TH1D*)GetChildren().front()) -> RemoveStamp();
  GetRef() = new THStack(
			 ((HStructure_worker*)GetChildren().front()) -> GetPtr() -> GetName(), 
			 ((HStructure_worker*)GetChildren().front()) -> GetPtr() -> GetTitle() );
  ((HStructure_TH1D*)GetChildren().front()) -> Stamp();

  for (unsigned char child_ind = 0; child_ind < GetChildren().size(); child_ind ++)
    {
      Get() -> Add(*(HStructure_TH1D*)GetChildren()[child_ind]);

       /*TH1D *h = (*pool)["numb_events_selection_stagesSELECTOR_BASE"];

	Table table_h("SELECTER_BASE", "SELECTOR_BASE");
	table_h.FillFromLabeledHistogram(h);
	table_h.ls();
	getchar();*/
    }
}

TLegend * HStructure_THStack::GetLegend() const
{
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  TList * list = Get() -> GetHists();
  TObject *obj = list -> First();
  unsigned char ind = 0;
  while (obj)
    {
      legend -> AddEntry(obj, GetChildren()[ind] -> GetTitle(), "f");
      obj = list -> After(obj);
      ind ++;
    }
  return legend;
}

THStack * HStructure_THStack::Get() const 
{
  return (THStack*) worker;
}

/*THStack *& HStructure_THStack::GetRef()
{
  return (THStack*) worker;
  }*/

THStack * HStructure_THStack::operator -> ()
{
  return (THStack*) worker;
}

THStack & HStructure_THStack::operator * ()
{
  return *(THStack*) worker;
}

const char * HStructure_THStack::WhoAmI() const
{
  return "HStructure_THStack";
}

HStructure_THStack::~HStructure_THStack()
{

}
