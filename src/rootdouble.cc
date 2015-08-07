#include "LIP/TauAnalysis/interface/rootdouble.h"
ClassImp(rootdouble);

rootdouble::rootdouble()
{
  information = 0;
}

rootdouble::rootdouble(const char* name, const char *title) : TNamed(name, title)
{
  information = 0;
}

double rootdouble::GetInformation() const
{
  return information;
}

void rootdouble::SetInformation(const double info)
{
  information = info;
}

rootdouble::~rootdouble()
{

}
