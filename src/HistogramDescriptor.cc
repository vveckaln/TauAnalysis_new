#include "TauAnalysis/interface/HistogramDescriptor.hh"

void HistogramDescriptor::ls() const
{
  printf("histogram title %s Xaxis title %s Yaxis title %s, number of bins %u, xlow %f, xup %f\n", histogram_title.Data(), Xaxis_title.Data(), Yaxis_title.Data(), nbinsx, xlow, xup);
}

SampleDescriptor::SampleDescriptor()
{
}

const char* SampleDescriptor::GetChildID() const
{
  const char *p = ID;
  while( *p!='\0') 
    p++;
  while(*p!='_') 
    p--; 
  p++;
  return p;
}
const char* SampleDescriptor::GetParent() const
{
  const char *p = ID;
  char *parent = new char[16];
  while( *p!='\0') 
    p++;
  while(*p!='_') 
    {
      p--;
      if (p == ID) 
	{
	  parent[0] = '0'; 
	  parent[1] = '\0';
	  return parent;
	}
    }
  
  p++;
  unsigned char i = 0;
  for(const char *p2 = ID; p2 != p; i ++, p2++)
    {
      parent[i] = *p2; 
      }
  parent[i-1] = '\0';
  const char * ret = parent;
  return ret;
}

const char* SampleDescriptor::GetName() const
{
  return sample_name.Data();
}

const char* SampleDescriptor::GetTitle() const
{
  return sample_title.Data();
}

void SampleDescriptor::SetName(const char * name)
{
  sample_name = name;
}

void SampleDescriptor::SetTitle(const char * title) 
{
  sample_title = title;
}

void SampleDescriptor::ls() const
{
  printf("name %s, title %s, color %u, marker style %u ID %s\n", sample_name.Data(), sample_title.Data(), fill_color, marker_style, ID);
}

SampleDescriptor::~SampleDescriptor()
{
}
