#ifndef _HistogramDescriptor_hh
#define _HistogramDescriptor_hh
#include "TString.h"
struct HistogramDescriptor
{
  TString       histogram_title;
  TString       histogram_name;
  TString       Xaxis_title;
  TString       Yaxis_title;
  int           nbinsx;
  double        xlow;
  double        xup;
  void ls() const;
};

struct SampleDescriptor
{
  TString       sample_title  {"no title"};
  TString       sample_name   {"no_name"};
  Color_t       fill_color    {kWhite};
  Style_t       marker_style  {1};
  const char*   ID            {"1"};
  SampleDescriptor();
  const char* GetParent() const;
  const char* GetChildID() const;
  const char * GetName() const;
  const char * GetTitle() const;
  void SetName(const char *);
  void SetTitle(const char *);
  void ls() const;
  virtual ~SampleDescriptor();
};
#endif
