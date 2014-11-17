#ifndef _DataSampleDescriptor_hh
#define _DataSampleDescriptor_hh
#include "TString.h"
struct DataSampleDescriptor{
  TString datasample_identifier;
  Color_t basic_hue;
  int     hue_adjustment;
  Style_t marker_style;
  TString legend_entry;
};
#endif
