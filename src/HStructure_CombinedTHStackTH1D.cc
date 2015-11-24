#include "CERN_RTU/TauAnalysis/interface/HStructure_CombinedTHStackTH1D.hh"
#include "CERN_RTU/TauAnalysis/interface/HStructure_TH1D.hh"
#include "CERN_RTU/TauAnalysis/interface/HStructure_THStack.hh"

HStructure_CombinedTHStackTH1D::HStructure_CombinedTHStackTH1D()
{
}

HStructure_CombinedTHStackTH1D::HStructure_CombinedTHStackTH1D(const SampleDescriptor & other):
  HStructure_worker(other)
{
}

HStructure_CombinedTHStackTH1D::HStructure_CombinedTHStackTH1D(const HStructure & structure): HStructure_worker(structure)
{
}

void * HStructure_CombinedTHStackTH1D::operator new (size_t size)
{
  return ::new HStructure_CombinedTHStackTH1D;
}

void HStructure_CombinedTHStackTH1D::FillBottomUp(const char *option)
{
  HStructure_worker::FillBottomUp(option);
  if (TString(option) != "iter") return;
  if(TestBit(kIsFilled)) 
    return;
  Join();
  Process();
}

HStructure_TH1D * HStructure_CombinedTHStackTH1D::GetChild_data() const
{
  for (unsigned char ind = 0; ind < GetChildren().size(); ind ++)
    {
      if (GetChildren()[ind] -> TestBit(kIsData)) 
	return (HStructure_TH1D*) GetChildren()[ind];
    }
  return NULL;
}

HStructure_THStack * HStructure_CombinedTHStackTH1D::GetChild_MC() const
{
  for (unsigned char ind = 0; ind < GetChildren().size(); ind ++)
    {
      if (not GetChildren()[ind] -> TestBit(kIsData)) 
	return (HStructure_THStack*) GetChildren()[ind];
    }
  return NULL;
}


/*void HStructure_CombinedTHStackTH1D::AddChild_TH1D(HStructure_TH1D * structure)
{
  th1d_structure = structure;
  HStructure::AddChild(structure);
}

void HStructure_CombinedTHStackTH1D::AddChild_THStack(HStructure_THStack * structure)
{
  thstack_structure = structure;
  HStructure::AddChild(structure);
  }*/

void HStructure_CombinedTHStackTH1D::Join()
{
  GetRef() = new CombinedTHStackTH1D;
  Get() -> th1d = GetChild_data() -> Get();
  Get() -> thstack = GetChild_MC() -> Get();
}

TLegend * HStructure_CombinedTHStackTH1D::CreateLegend()
{
  TLegend* legend = GetChild_MC() -> GetLegend();
  Get() -> legend = legend;
  return legend;
}
void HStructure_CombinedTHStackTH1D::Process()
{
  CreateLegend();
  Get() -> UpdateLegend(); 
  Get() -> graph = Get() -> CreateRatioGraph();
  
  Get() -> canvas = Get() -> ProduceDrawing();
}

CombinedTHStackTH1D * HStructure_CombinedTHStackTH1D::Get()
{
  return (CombinedTHStackTH1D*)worker;
}

CombinedTHStackTH1D & HStructure_CombinedTHStackTH1D::operator *()
{
  return *(CombinedTHStackTH1D*) worker;
}

CombinedTHStackTH1D * HStructure_CombinedTHStackTH1D::operator -> ()
{
  return (CombinedTHStackTH1D*)worker;
}

const char* HStructure_CombinedTHStackTH1D::WhoAmI() const
{
  return "HStructure_CombinedTHStackTH1D";
}
  
HStructure_CombinedTHStackTH1D:: ~HStructure_CombinedTHStackTH1D()
{
}
