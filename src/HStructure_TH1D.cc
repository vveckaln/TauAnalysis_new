#include "LIP/TauAnalysis/interface/HStructure_TH1D.hh"
//#include "LIP/TauAnalysis/interface/Table.h"

#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"
//#include "LIP/TauAnalysis/interface/CPFileRegister.hh"

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
  return ::new HStructure_TH1D;
}

void HStructure_TH1D::PopulateWorkingElements(const char * option)
{
  
  //IterateDown(&HierarchicalStructure_worker::PopulateWorkingElements, option);
}

void HStructure_TH1D::FillBottomUp(const char *option)
{
  HStructure_worker::FillBottomUp(option);
  if (TString(option) != "iter") return;
  if(TestBit(kIsFilled)) 
    return;
  SetBit(kIsStamped, ((HStructure_TH1D*)GetChildren().front()) -> TestBit(kIsStamped));
  GetRef() = (TH1D*)((HStructure_TH1D*)GetChildren().front()) -> Get() -> Clone();
  FixStamp();
  Get() -> Reset();
  for (unsigned char child_ind = 0; child_ind < GetChildren().size(); child_ind ++)
    {
      Get() -> Add(*(HStructure_TH1D*)children[child_ind]);
      /*  TH1D *h = (*pool)["numb_events_selection_stagesSELECTOR_BASE"];

       Table table_h("SELECTER_BASE", "SELECTOR_BASE");
	table_h.FillFromLabeledHistogram(h);
	table_h.ls();
	getchar();*/
    }
  Get() -> SetFillColor(fill_color);
 
  /*printf("total after filling\n");
  TH1D *h = (*(HistogramPool*)working_element)["numb_events_selection_stagesSELECTOR_BASE"];

       Table table_h("SELECTER_BASE", "SELECTOR_BASE");
	table_h.FillFromLabeledHistogram(h);
	table_h.ls();
	getchar();*/
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
  if (TestBit(kIsStamped) and not Get()) return;
  
  char name[128];
  sprintf(name, "%s_%u\n", Get() -> GetName(), GetHistID());
  Get() -> SetName(name);
  SetBit(kIsStamped, true);
}

void HStructure_TH1D::RemoveStamp()
{
  if (not TestBit(kIsStamped) and not Get()) return;
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
