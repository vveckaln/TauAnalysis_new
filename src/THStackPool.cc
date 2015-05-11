#include "LIP/TauAnalysis/interface/THStackPool.hh"
#include <iostream>
#include "TList.h"
using namespace std;

THStackPool::THStackPool()
{
  legend = NULL;
}

THStackPool::THStackPool(const vector<HistogramDescriptor> * object_descriptors)
{
  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++)
    {
      THStack *obj = new THStack(
				 object_descriptors -> at(obj_ind).histogram_title, 
				 object_descriptors -> at(obj_ind).histogram_title
				 );
      object_map[object_descriptors -> at(obj_ind).histogram_title] = obj;
    } 
 
}

void THStackPool::AddObjects(const vector<HistogramDescriptor> * object_descriptors, const char* append)
{
  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++)
    {
      THStack *obj = new THStack(
				 object_descriptors -> at(obj_ind).histogram_title + append, 
				 object_descriptors -> at(obj_ind).histogram_title + append
				 );
      object_map[object_descriptors -> at(obj_ind).histogram_title + append] = obj;
      printf("adding %s %s\n", obj -> GetName(), object_descriptors -> at(obj_ind).histogram_title.Data());
    } 
 
}

TLegend* THStackPool::DrawLegend()
{
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  /*TList * list = object_map.begin() -> second -> GetHists();
  TObject *obj = list -> First();
  unsigned char ind = 0;
  while (obj)
    {
      legend -> AddEntry(obj, this -> hierarchy -> GetChildren()[ind] -> sample_descriptor.sample_title, "pf");
      obj = list -> After(obj);
      ind ++;
      }*/
    return legend;
}

THStackPool::~THStackPool()
{
  printf("Deconstructing THStackpool\n");
}

