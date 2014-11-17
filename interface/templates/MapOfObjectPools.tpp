#include "LIP/TauAnalysis/interface/Parser.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"

#include "TAxis.h"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
#include "TH1D.h"

#include <iostream>
using namespace gVariables;
template<class Object>
MapOfObjectPools<Object>::MapOfObjectPools(){
  printf("Default MapOfObjectPools constructor\n");
}

/*
template<class Object>
ObjectPool<Object>::ObjectPool(const vector<HistogramDescriptor> * object_descriptors){
  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++){
    Object *obj = new Object();
    obj -> SetTitle(object_descriptors -> at(obj_ind).histogram_title);
    obj -> SetName(object_descriptors -> at(obj_ind).histogram_title);
    TAxis *xaxis = obj -> GetXaxis();
    xaxis -> Set(object_descriptors -> at(obj_ind).nbinsx,
	  object_descriptors -> at(obj_ind).xlow,
	  object_descriptors -> at(obj_ind).xup
	  );
    xaxis -> SetTitle(object_descriptors -> at(obj_ind) . Xaxis_title);
    TAxis *yaxis = obj -> GetYaxis();
    yaxis -> SetTitle(object_descriptors -> at(obj_ind) . Yaxis_title);
    object_map[object_descriptors -> at(obj_ind).histogram_title] = obj;
  } 
 
}
*/
/*
template<class Object>
Object *& ObjectPool<Object>::at(const TString key){
  return object_map[key];
}
*/
/*
template<class Object>
Object *& ObjectPool<Object>::operator [](const TString key){
  return object_map[key];
}
*/
/*
template<class Object>
unsigned long ObjectPool<Object>::size() const{
  return object_map . size();
}
*/
/*
template<class Object>
ObjectPool<Object>* ObjectPool<Object>::Clone(const char * append )const{
  ObjectPool<Object> * new_pool = new ObjectPool();
  // ObjectPool<Object> * new_pool = static_cast<ObjectPool<Object>*>(:: new ObjectPool());
  for (typename map<TString, Object*>::const_iterator cit = object_map.cbegin(); cit != object_map.cend(); ++cit){
    new_pool -> object_map[cit -> first] = (Object*)object_map.at(cit->first) -> Clone(cit -> first + append);
  }
  return new_pool;
}
*/

template<class Object>
ObjectPool<Object>* MapOfObjectPools<Object>::GetObjectPool(const char * title )const
{
  return const_cast<ObjectPool<Object>*>(ObjectPool_map.at(title));
}
/*
template<class Object>
void ObjectPool<Object>::Reset() const {
  for (typename map<TString, Object*>::const_iterator cit = object_map.cbegin(); cit != object_map.cend(); ++cit){
    cit -> second -> Reset();
  }
}
*/
/*
template<class Object>
void ObjectPool<Object>::SetXaxesTitle(const vector<HistogramDescriptor> * object_descriptors) const{
  for (unsigned char ind = 0; ind < object_descriptors -> size(); ind ++){
    object_map.at(object_descriptors -> operator[](ind) . histogram_title) -> GetXaxis() -> SetTitle(object_descriptors -> operator[](ind) . Xaxis_title);
  }
}
*/
/*
template<class Object>
void ObjectPool<Object>::SetAllYaxesTitle(const char * title) const{
  for (typename map<TString, Object *>::const_iterator cit = object_map.cbegin(); cit != object_map.cend(); ++cit){
    cit -> second -> GetYaxis() -> SetTitle(title);
   }
}
*/
/*
template<class Object>
void ObjectPool<Object>::SetYaxesTitle(const vector<HistogramDescriptor> * object_descriptors) const{
  for (unsigned char ind = 0; ind < object_descriptors -> size(); ind ++){
    object_map.at(object_descriptors -> operator[](ind) . histogram_title) -> GetYaxis() -> SetTitle(object_descriptors -> operator[](ind) . Yaxis_title);
  }
}
*/
/*
template<class Object>
void ObjectPool<Object>::Sumw2() const{
  for (typename map<TString, Object *>::const_iterator cit = object_map.cbegin(); cit != object_map.cend(); ++cit){
    cit -> second -> Sumw2();
   }
}
*/
/*
template<class Object>
void ObjectPool<Object>::GetFromFile(const vector<HistogramDescriptor> * object_descriptors, TFile * input_file){
    for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++){
    object_map[object_descriptors -> at(obj_ind).histogram_title] = (Object*) input_file -> Get(object_descriptors -> at(obj_ind).histogram_title);

  }
}
*/
template<class Object>
void MapOfObjectPools<Object>::ls() const{
  printf("******** Begin list of MapOfObjectPools contents ********\n");

  unsigned ind = 0;
  
  for (typename map<TString, ObjectPool<Object> *>::const_iterator cit = ObjectPool_map.cbegin(); cit != ObjectPool_map.cend(); ++cit, ind ++){
    printf("%u ObjectPool name: %s\n", ind, cit -> second -> GetTitle().Data());
   }
   printf("******** End list of MapOfObjectPools contents ********\n");
}

template<class Object>
void MapOfObjectPools<Object>::Write()
{
  cpFileRegister::output_file -> cd();
  for (typename map<TString, ObjectPool<Object> *>::const_iterator cit = ObjectPool_map.cbegin(); cit != ObjectPool_map.cend(); ++ cit)
  {
    cit -> second -> Write();
   }
}

template<class Object>
void MapOfObjectPools<Object>::Close()
{
  for (typename map<TString, ObjectPool<Object> *>::const_iterator cit = ObjectPool_map.begin(); 
  cit != ObjectPool_map.end(); ++ cit)
  {
    cit -> second -> Close();
  }
}


template<class Object>
MapOfObjectPools<Object>::~MapOfObjectPools()
{
  printf("Closing - ObjectPool_map size %lu\n", ObjectPool_map.size());
  for (typename map<TString, ObjectPool<Object> *>::const_iterator cit = ObjectPool_map.cbegin(); 
  cit != ObjectPool_map.cend(); ++ cit)
  {
    delete cit -> second;
  }
  ObjectPool_map . clear();
}

/*
template<class Object>
void ObjectPool<Object>::SetFillColor(Color_t color){
  for (it = object_map.begin(); it != object_map.end(); ++it){
    it -> second -> SetFillColor(color);
  } 
}
*/
/*
template<class Object>
void ObjectPool<Object>::SetMarkerStyle(Style_t style){
  for (it = object_map.begin(); it != object_map.end(); ++it){
    it -> second -> SetMarkerStyle(style);
  } 
}
*/

template<class Object>
void MapOfObjectPools<Object>::Add(ObjectPool<Object> *other)
{
  ObjectPool_map[other -> GetTitle()] = other;
}

/*
template<class Object>
template<class OtherObject>
void ObjectPool<Object>::Add(ObjectPool<OtherObject> *other, const char * option){
  for (it = object_map.begin(); it != object_map.end(); ++it){
    it -> second -> Add(other -> object_map . at(it -> first), option);
  } 
}
*/


