#ifndef __rootdouble__
#define __rootdouble__
#include "TObject.h"
#include "TNamed.h"
class rootdouble :  public TNamed
{
double information;

public: 
  rootdouble();
  rootdouble(const char* name, const char *title);
  double GetInformation() const;
  void SetInformation(const double);
  virtual ~rootdouble();
  ClassDef(rootdouble, 1);
};
#endif
