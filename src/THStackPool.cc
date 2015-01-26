#include "LIP/TauAnalysis/interface/THStackPool.hh"
#include <iostream>
using namespace std;

THStackPool::THStackPool(){
}

THStackPool::THStackPool(const vector<HistogramDescriptor> * object_descriptors){
  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++){
    THStack *obj = new THStack(
			  object_descriptors -> at(obj_ind).histogram_title, 
			  object_descriptors -> at(obj_ind).histogram_title
			  );
    object_map[object_descriptors -> at(obj_ind).histogram_title] = obj;
  } 
 
}

void THStackPool::AddObjects(const vector<HistogramDescriptor> * object_descriptors){
  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++){
    THStack *obj = new THStack(
			  object_descriptors -> at(obj_ind).histogram_title, 
			  object_descriptors -> at(obj_ind).histogram_title
			  );
    object_map[object_descriptors -> at(obj_ind).histogram_title] = obj;
  } 
 
}

THStackPool::~THStackPool(){
  printf("Deconstructing THStackpool\n");
}

