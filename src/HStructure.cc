#include "LIP/TauAnalysis/interface/HStructure.hh"
#include "LIP/TauAnalysis/interface/HStructure_TH1D.hh"
#include "LIP/TauAnalysis/interface/HStructure_THStack.hh"
#include "LIP/TauAnalysis/interface/HStructure_TFile.hh"
#include "LIP/TauAnalysis/interface/Utilities.hh"

#include "LIP/TauAnalysis/interface/Register.hh"
using namespace utilities;

HStructure::HStructure()
{
}

HStructure::HStructure(const SampleDescriptor & other) : SampleDescriptor(other)
{
}

const HStructure * const HStructure::iterator::END = new HStructure();
const HStructure * const HStructure::iterator::ITER = new HStructure();

HStructure::iterator::iterator()
{
}

HStructure::iterator::iterator(HStructure * to): generator(to), to(to)
{
}

HStructure *& HStructure::iterator::GetRefGenerator(HStructure::iterator & other)
{
  return other.generator;
}

HStructure *& HStructure::iterator::GetRefTo(HStructure::iterator & other)
{
  return other.to;
}

HStructure::iterator HStructure::iterator::operator ++(int)
{
  HStructure::iterator previous = *this;
  increment();
  return previous; 
}

HStructure::iterator HStructure::iterator::operator ++()
{
  increment();
  return *this; 
}

HStructure::iterator HStructure::iterator::operator -- ()
{
  decrement();
  return *this; 
}

HStructure::iterator & HStructure::iterator::increment(const char * option)
{
  if (to == const_cast<HStructure*>(ITER))
    return *this;
  if (to -> Next(option) == NULL and not TestOption(option, "children"))
    to = const_cast<HStructure*>(END);
  else
    {
      if (TestOption(option, "children") and to -> Next("children") == NULL)
	{
	  if (to -> Next())
	    to = to -> Next();
	  else
	    to = const_cast<HStructure*>(END);
	}
      else
	to = to -> Next(option);
    }
  return *this; 
}

HStructure::iterator & HStructure::iterator::decrement(const char * option)
{
  if (to == const_cast<HStructure*>(ITER))
    return *this;
  if (to == const_cast<HStructure*>(END))
    {
      to = generator -> Last();
    }
  else 
    {
      if (TestOption(option, "children"))
	{
	  if (to -> Previous("children") == NULL)
	    {
	      to = to -> Previous();
	    }
	  else
	    {
	      to = to -> Previous(option);
	    }
	}
      else
	{
	  to = to -> Previous(option);
	}
    }
  return *this; 
}

HStructure * HStructure::iterator::operator -> ()
{
  return to;
}

HStructure & HStructure::iterator::operator *()
{
  return *to;
}

bool HStructure::iterator::operator != (const HStructure * other)
{  
  return to != other;
}

bool HStructure::iterator::operator == (const HStructure * other)
{  
  return to == other;
}

bool HStructure::iterator::operator != (const HStructure::iterator & other)
{  
  return to != other.to;
}

HStructure::iterator & HStructure::iterator::operator = (HStructure * other)
{  
  if (other)
    to = other;
  else to = const_cast<HStructure*>(END);
  generator = other;
  return * this;
}

void * HStructure::operator new (size_t size)
{
  return ::new HStructure();
}

void * HStructure::operator new (size_t size, const SampleDescriptor & sample)
{
  return ::new HStructure(sample);
}

unsigned char HStructure::GetStatusBits() const
{
  return StatusBits;
}

void HStructure::SetStatusBits(const unsigned char bits)
{
  StatusBits = bits;
}

void HStructure::something()
{
  printf("kOpenForInput %u kOpenForOutput %u\n", kOpenForInput, kOpenForOutput);  
}

HStructure::iterator HStructure::begin(const char* option) const
{
  HStructure::iterator ret;
  if (TestOption(option, "iter")) 
    {
      ret = const_cast<HStructure*>(iterator::ITER);
      return ret;
    }
  ret = const_cast<HStructure*>(this);;
  if (TestOption(option, "children") or TestOption(option, "descendants"))
    {
      if (GetChildren().size() == 0)
	{
	  ret = const_cast<HStructure*>(iterator::ITER);
	  return ret;
	}
      ret = children.front();
    }
  return ret;
}

HStructure::iterator HStructure::end(const char* option) const
{
  HStructure::iterator ret;
  if (TestOption(option, "iter"))
    {
      ret = const_cast<HStructure*>(iterator::ITER);

      return ret;
    }
  if (TestOption(option, ""))
    {
      ret = const_cast<HStructure*>(this -> Next());
    }
  else if (TestOption(option, "children"))
    {
      if (GetChildren().size() == 0)
	{
	  ret = const_cast<HStructure*>(iterator::ITER);
	  return ret;
	}
      ret = GetChildren().back() -> Next();
      ret.generator = (HStructure*)this;
    }
  else if (TestOption(option, "all") or TestOption(option, "descendants"))
    {
      ret  . to = const_cast<HStructure*>(iterator::END);
      ret.generator = (HStructure*)this; //= (HStructure*)NULL;
    }
   
  return ret;
}  

HStructure * HStructure::Clone(const char * option)
{
  const TString comp(option);
  if (comp == "children" or comp == "descendants")
    {
      printf("Cloning can only be performed from vertex, returning NULL\n");
      return NULL;
    }
  printf("cloning %s\n", this -> WhoAmI());
  
  HStructure * ret = (HStructure*)this -> operator new(sizeof(this)/*, *(const SampleDescriptor *) this*/);
  // ret -> SetBit(kIsCloned, true);
  //ret -> sample_descriptor = sample_descriptor;
   if (option = "all")
  for (unsigned char ind = 0; ind < children.size(); ind ++)
    {
      ret -> AddChild(children[ind] -> Clone("all"));
    }
  return ret;
}

HStructure * HStructure::Next(const char * option) const
{
  
  if (TestOption(option, "children"))
    return const_cast<HStructure*>(GetNextSibling());
  if (children.size() > 0)
    return children[0];
  else
    {
      const HStructure * ret = this;
      while (ret -> Parent() and not ret -> GetNextSibling())
	{
	  ret = ret -> Parent();
	}
      return const_cast<HStructure*>(ret -> GetNextSibling());
    }
  return NULL;
}  

HStructure * HStructure::GetHStructure(const char * sample_name) const
{
  const HStructure * ret = this;
  bool found = false; 
  while(not found and ret)
    {
      found = ret -> sample_name == TString(sample_name);
      if (not found) 
	ret = ret -> Next();
    }
  
  return const_cast<HStructure*>(ret);
}

HStructure * HStructure::Last()
{
  HStructure * ret = this;
  while(ret -> Next())
    {
      ret = ret -> Next();
    }
  
  return ret;
}

void HStructure::SetParent(HStructure * parent)
{
  this -> parent = parent;
}

HStructure * HStructure::Parent() const
{
  return parent;
}

vector<HStructure *> & HStructure::GetChildren() 
{
  return children;
}

const vector<HStructure *> & HStructure::GetChildren() const
{
  return children;
}

HStructure * HStructure::GetNextSibling() const
{
  if (not Parent())
    return NULL;
  return Parent() -> GetNextChild(this);
}

HStructure * HStructure::GetNextChild(const HStructure * this_child) const
{
  unsigned char ind = 0;
  do
    {
      ind ++;
    } while(ind < children.size() and children[ind -1] != this_child);
  if (ind == children.size())
    return NULL;
  else 
    return children[ind];
  return NULL;
}

HStructure * HStructure::GetPreviousChild(const HStructure * this_child) const
{
  char ind = children.size() - 1;
  do
    {
      ind --;
    } while(ind > -1 and children[ind + 1] != this_child);
  if (ind == -1)
    return NULL;
  else 
    return children[ind];
  return NULL;
}

HStructure * HStructure::GetPreviousSibling() const
{
  if (not Parent())
    return NULL;
  return Parent() -> GetPreviousChild(this);
}

HStructure * HStructure::Previous(const char * option) const
{
  if (TestOption(option, "children"))
    return const_cast<HStructure*>(GetPreviousSibling());
  if (not GetPreviousSibling())
    return Parent();
  else
    {
      const HStructure * ret = GetPreviousSibling();
      while (ret ->  GetChildren().size() != 0)
	{
	  ret = ret -> GetChildren().back();
	  //printf( "iterate\n"); ret -> lsSample(); getchar();
	}
      return const_cast<HStructure*>(ret);
    }
  //getchar();
  return NULL;
}

void HStructure::IterateDown(void (HStructure::*func)(const char*), const char * option)
{
   const TString comp = option;
  if (comp != "all" and comp != "descendants" and comp != "children") 
    {
      return;
    }
  for (unsigned char ind = 0; ind < children.size(); ind ++)
    {
      if (comp == "children")
	(children[ind] ->* func)("");
      else
	(children[ind] ->* func)("all");
    }
}

void HStructure::IterateDown(void (HStructure::*func)(const char*) const, const char * option) const
{
   const TString comp = option;
  if (comp != "all" and comp != "descendants" and comp != "children") 
    {
      return;
    }
  for (unsigned char ind = 0; ind < children.size(); ind ++)
    {
      if (comp == "children")
	(children[ind] ->* func)("");
      else
	(children[ind] ->* func)("all");
    }
}

void printb(const unsigned numb)
{
  printf("numb = %u ", numb);
  unsigned char arr[8];
  for (unsigned char ind = 0; ind < 8; ind ++)
    arr[ind] =  numb >> ind & 1;
  for (unsigned char ind = 8; ind != 0; ind --)
    printf("%u", arr[ind - 1]);
  printf("\n");
}

bool HStructure::TestBit(unsigned char bit) const
{
  return StatusBits >> bit & 1;
}

void HStructure::SetBit(unsigned char bit, bool value, const char * option)
{
  const unsigned char mask_for_number = 1 << bit;
  const unsigned char mask_for_bool = not value << bit;
  const unsigned char number_neutral = StatusBits | mask_for_number;
  const char neg_number = ~number_neutral;
  const char neg_mask_for_bool = ~mask_for_bool;
  StatusBits = number_neutral & neg_mask_for_bool | neg_number & mask_for_bool;
  for (HStructure::iterator it = begin(option); it != end(option); it.increment(option))
    {
      it -> SetBit(bit, value, "iter");
    }

}



  
void HStructure::ls(const char * option) const
{
 
  printf("\nlisting hierarchical structure\n");
  
   lsSample();
   printf("type %s\n", WhoAmI());
   printf("address %p\n", this); 
   /* printf("parent_info: ");
   if (Parent()) 
     {
       printf("ID %s type %s \n", Parent() -> sample_descriptor.ID, Parent() -> WhoAmI());
     }
   else 
   printf("no parent\n");*/
   /* printf("LISTING NEXT %p\n", Next());
       if (Next())
	 Next() -> ls();
       else
	 printf("no next\n");
       printf("Listing next sibling\n");
       if (GetNextSibling())
	 GetNextSibling() -> ls();
       else
       printf("no next sibling\n");*/
   if (TString(option) == "all" or TString(option) == "children")
     {
       if (children.size() > 0)
	 {
	   printf("listing children and structures below each child\n");
	 }
       else 
	 printf("no children\n");
       
       IterateDown(&HStructure::ls, option);
     }
}

void HStructure::ls_bckw(const char * option)
{
  for (HStructure::iterator it = --end(option); it != --begin(option); it.decrement(option))
    {
      it -> test(AddOptions(option, "iter").Data());
    }

}

void HStructure::test(const char * option) 
{
 
  if (TestOption(option, "iter")) goto cont; 
  for (HStructure::iterator it = begin(option); it != end(option); it.increment(option))
    {
      
      it -> test(AddOptions(option, "iter").Data());
     
    }
  return;
  cont:
  printf("\nlisting hierarchical structure\n");
  lsSample();
  if (TestOption(option, "sample")) 
    return;    
  printf("this %p StatusBits %u IsData %s type %s\n", this, StatusBits, to_char(TestBit(kIsData)), WhoAmI());
  printf("parent_info: ");
  if (Parent()) 
    {
      printf("ID %s type %s \n", Parent() -> ID, Parent() -> WhoAmI());
    }
  else 
    printf("no parent\n");
  if (TestOption(option, "all") or TestOption(option, "children"))
    {
      if (GetChildren().size() > 0)
	{
	  printf("listing children and structures below each child\n");
	}
      else 
	printf("no children\n");
   }
    
}

void HStructure::lsSample() const 
{
  SampleDescriptor::ls();
}

void HStructure::Write(const char * option)
{
  IterateDown(&HStructure::Write, option);
}

void HStructure::Delete(const char * option)
{
  IterateDown(&HStructure::Delete, option);
}

void HStructure::AddChild(HStructure * child)
{
  const char * append = GetChildID();
  const char * prefix;
  HStructure * this_pointer = this;
  if (child)
    {
      children.push_back(child);
      child -> parent = this;
      append = to_string(children.size()).c_str();
      this_pointer = child;
      prefix = ID;
    }
  else
    {
      prefix = parent -> ID;
    }
  char * child_ID = new char[32];
  unsigned char ind = 0;
  for (const char * p = prefix; *p != '\0'; p ++, ind ++)
    {
      child_ID[ind] = *p;
    }
  child_ID[ind] = '_';
  ind ++;
  for (const char * p = append; *p != '\0'; p ++, ind ++)
    {
      child_ID[ind] = *p;
    }
  child_ID[ind] = '\0';
  this_pointer -> ID = child_ID;
  for (unsigned char child_ind = 0; child_ind < this_pointer -> children.size(); child_ind ++)
    {
      this_pointer -> children[child_ind] -> AddChild(NULL);
    }
}

void HStructure::OrderChildren()
{
  bool ordered = false; 
  do
    {
      ordered = true;
      
      for (unsigned char child_ind = 0; child_ind < (children.size() - 1); child_ind ++)
	{
	  const char * child_ID = children[child_ind] -> GetChildID();
	  unsigned char child_ID_int = atoi(child_ID);

	  const char * child_ID_next = children[child_ind + 1] -> GetChildID();
	  unsigned char child_ID_next_int = atoi(child_ID_next);
	  if (child_ID_int > child_ID_next_int)
	    {
	       HStructure *store = children[child_ind];
	       children[child_ind] = children[child_ind + 1];
	       children[child_ind + 1] = store;
	       ordered = false;
	    }
	} 
    }while (not ordered);
}

const char* HStructure::WhoAmI() const
{
  return "HStructure";
}

HStructure::~HStructure()
{

}

bool TestOption(const char *option, const char * comparison)
{
  if (TString(comparison) == "")
    return TString(comparison) == TString(option);
  return TString(option).Contains(TString(comparison));
}

TString AddOptions(const char *option1, const char* option2)
 {
   return TString(option1) + option2;
 }

