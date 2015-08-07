#include "LIP/TauAnalysis/interface/HStructure_TFile.hh"

#include "LIP/TauAnalysis/interface/HStructure_THStack.hh"
#include "LIP/TauAnalysis/interface/HStructure_TH1D.hh"
#include "LIP/TauAnalysis/interface/HStructure_CombinedTHStackTH1D.hh"
#include "LIP/TauAnalysis/interface/HStructure_worker.hh"
#include "LIP/TauAnalysis/interface/Register.hh"

HStructure_TFile::HStructure_TFile()
{
}

HStructure_TFile::HStructure_TFile(const  HStructure &structure) : HStructure(structure)
{
}

HStructure_TFile::iterator::iterator(HStructure * to): HStructure::iterator(to)
{
}

HStructure_TFile * HStructure_TFile::iterator::operator -> ()
{
  return (HStructure_TFile*) to;
}

HStructure_TFile & HStructure_TFile::iterator::operator * ()
{
  return *(HStructure_TFile*) to;
}

void * HStructure_TFile::operator new (size_t size)
{
  return ::new HStructure_TFile;
}

void * HStructure_TFile::operator new (size_t size, const SampleDescriptor & sample)
{
  printf("calling this constructor\n");
  return ::new HStructure_TFile(sample);
}

const char * HStructure_TFile::WhoAmI() const
{
  return "HStructure_TFile";
}

HStructure_TFile::iterator::iterator(HStructure::iterator&& other)
{
  to = GetRefTo(other);
  GetRefTo(other) = NULL;
  generator = GetRefGenerator(other);
  GetRefGenerator(other) = NULL;
}

TFile & HStructure_TFile::operator *() 
{
  return *file;
}

TFile * HStructure_TFile::operator -> () 
{
  return file;
}

TFile * HStructure_TFile::GetFile() 
{
  return file;
}

TFile *& HStructure_TFile::GetRef() 
{
  return file;
}
HStructure_TFile & HStructure_TFile::operator = (TFile *f)
{
  file = f;
  return *this;
}
void HStructure_TFile::cd()
{
  cpregister::active_HStructure_TFile = this;
}

HStructure_TFile* HStructure_TFile::Open(const char* name, Option_t* option )
{
  HStructure_TFile * ret = new HStructure_TFile;
  ret -> GetRef() = TFile::Open(name, option);
  TFile *f = ret -> GetFile();
  if (not f || not f -> IsOpen() || f -> IsZombie() || f -> TestBit(TFile::kRecovered))
    return NULL;
  return ret;
}

void HStructure_TFile::OpenForInput(const char * option, const char * directory)
{
  const TString file_name = TString(directory)
    + "/" + sample_name + "_TOTAL_out.root";
  printf("opening %s %s\n", directory, file_name.Data());
  if (TString(option) != "iter") {goto cont;} 
   
  file = TFile::Open(file_name, "READ"); 
  SetBit(kOpenForInput, true);
  if (not file || not file -> IsOpen() || file -> IsZombie() || file -> TestBit(TFile::kRecovered))
    SetBit(kOpenForInput, false);
  return;
  cont : for (HStructure_TFile::iterator it = begin(option); it != end(option); it.increment(option))
    {
      it -> OpenForInput("iter", directory);
    }
}

void HStructure_TFile::test2(const char *s1, const char * s2)
{
  printf("%s %s\n", s1, s2);
}

void HStructure_TFile::OpenForOutput(const char * option, const char * directory)
{
  if (TString(option) != "iter") goto cont; 

  if (TestBit(kOpenForInput)) return;
    file = new TFile(TString(directory) 
			    + "/" + sample_name + "_TOTAL_out.root", "RECREATE"); 
  SetBit(kOpenForOutput, true);
  if (not file || not file -> IsOpen() || file -> IsZombie() || file -> TestBit(TFile::kRecovered))
    SetBit(kOpenForOutput, false);
  return;
  cont : for (HStructure_TFile::iterator it = begin(option); it != end(option); it.increment(option))
    {
      it -> OpenForOutput("iter", directory);
    }
}

HStructure_worker * HStructure_TFile::Get(const char * name)
{
  HStructure_worker * ret;
  if (not Parent())
    {
      ret = new HStructure_CombinedTHStackTH1D(*(const SampleDescriptor*)this);
      
    }
  else if (not Parent() -> Parent())
    {
      if (TestBit(kIsData))
        ret = new HStructure_TH1D(*(const SampleDescriptor*)this);
      else
	ret = new HStructure_THStack(*(const SampleDescriptor*)this);
    }
  else
    {
      ret = new HStructure_TH1D(*(const SampleDescriptor*)this);
    }
  if (TestBit(kOpenForInput))
    {
      printf("%s %s %p\n", ((HStructure_TFile*)GetHStructure(ret -> GetName())) -> GetFile() -> GetName(), name, ret -> GetRef());

      ret -> GetRef() = (*(HStructure_TFile*)GetHStructure(ret -> GetName())) -> Get(name);
      printf("%p %p\n", ret -> GetRef(), ((HStructure_TH1D*)ret) -> Get());
      ((HStructure_TH1D*)ret) -> Get() -> SetFillColor(fill_color);
      ((HStructure_TH1D*)ret) -> Stamp();
    }
printf("%s \n", ret -> GetName() );

  if (ret -> GetPtr())
    ret -> SetBit(kIsFilled, true);
  ret -> SetBit(kIsData, TestBit(kIsData));
  for (unsigned char ind = 0; ind < children.size(); ind ++)
    {
      
      ret -> GetChildren().push_back(((HStructure_TFile*)children[ind]) -> Get(name));
      ret -> GetChildren().back() -> SetParent(ret);
    }
  return ret;
}

HStructure_worker * HStructure_TFile::Get1(const char * name)
{
  HStructure_worker * ret = new HStructure_TH1D(*(const SampleDescriptor*)this);
  
  if (TestBit(kOpenForInput))
    {
      ret -> GetRef() = (*(HStructure_TFile*)GetHStructure(ret -> GetName())) -> Get(name);
      ((HStructure_TH1D*)ret) -> Get() -> SetFillColor(fill_color);
      ((HStructure_TH1D*)ret) -> Stamp();
    }
  if (ret -> GetPtr())
    ret -> SetBit(kIsFilled, true);
  ret -> SetBit(kIsData, TestBit(kIsData));
  for (unsigned char ind = 0; ind < children.size(); ind ++)
    {
      
      ret -> GetChildren().push_back(((HStructure_TFile*)children[ind]) -> Get1(name));
      ret -> GetChildren().back() -> SetParent(ret);
    }
  return ret;
}

HStructure_worker * HStructure_TFile::GenerateWorker(const HistogramDescriptor & desc)
{
  HStructure_worker * ret;
  if (not Parent())
    {
      ret = new HStructure_worker(*(const SampleDescriptor*)this);
      
    }
  else
    {
      ret = new HStructure_TH1D(*(const SampleDescriptor*)this);
      ret -> GetRef() = new TH1D( desc . histogram_name.Data(), desc . histogram_title.Data(), desc . nbinsx, desc . xlow, desc . xup);
      ((HStructure_TH1D*)ret) -> Stamp();
      ((HStructure_TH1D*)ret) -> Get() -> GetXaxis() -> SetTitle(desc . Xaxis_title.Data());
      ((HStructure_TH1D*)ret) -> Get() -> GetYaxis() -> SetTitle(desc . Yaxis_title.Data());
    }
  
  ret -> SetBit(kIsData, TestBit(kIsData));
  for (unsigned char ind = 0; ind < children.size(); ind ++)
    {
      
      ret -> GetChildren().push_back(((HStructure_TFile*)children[ind]) -> GenerateWorker(desc));
      ret -> GetChildren().back() -> SetParent(ret);
    }
  return ret;
}

void HStructure_TFile::Close(const char * option)
{
  for (HStructure_TFile::iterator it = begin(option); it != end(option); it.increment(option))
    {
      it -> Close("iter");
    } 
  if (file)
    {
      file -> Close();
    }
}

/*void HStructure_TFile::ls(const char * option) const
{
}*/


void HStructure_TFile::test(const char * option) 
{
  HStructure::test(option);
  if (TString(option) != "iter") return;
  printf(" Opened for input %s;\n Opened for output %s;\n File %s;\n", 
	 TestBit(kOpenForInput) ? "true" : "false", 
	 TestBit(kOpenForOutput) ? "true" : "false",
	 file ? file -> GetName() : "no file"); 
  printf(" this %p\n", this); 
  if (TString(option) == "all" or TString(option) == "descendants")
    {
      if (children.size() > 0)
	printf("listing children and structures below each child\n");
      else
	printf("no children\n");
    }
}


HStructure_TFile::~HStructure_TFile()
{

}
