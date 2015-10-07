#include "LIP/TauAnalysis/interface/TCanvasPool.hh"
#include <iostream>
#include "LIP/TauAnalysis/interface/CPHistogramPoolRegister.hh"

using namespace cpHistogramPoolRegister;
using namespace std;

TCanvasPool::TCanvasPool(){
  TCanvas_map = &object_map;
  cd_pad = 0;
}

TCanvasPool::TCanvasPool(const vector<HistogramDescriptor> * object_descriptors){
  cd_pad = 0;
  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++){
    TCanvas *obj = new TCanvas(
			  object_descriptors -> at(obj_ind).histogram_title, 
			  object_descriptors -> at(obj_ind).histogram_title
			  );
    object_map[object_descriptors -> at(obj_ind).histogram_title] = obj;
  } 
  TCanvas_map = &object_map;
}

void TCanvasPool::AddObjects(const vector<HistogramDescriptor> * object_descriptors){
  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++){
    TCanvas *obj = new TCanvas(
			  object_descriptors -> at(obj_ind).histogram_title, 
			  object_descriptors -> at(obj_ind).histogram_title
			  );
    object_map[object_descriptors -> at(obj_ind).histogram_title] = obj;
  } 
}

void TCanvasPool::Update(){
  for (map<TString, TCanvas *>::iterator it = object_map.begin(); it != object_map.end(); ++it){
    object_map[it -> first] -> Update();
  }
}

void TCanvasPool::DrawOnAllCanvases(TObject *object, Option_t* option ){
  for (map<TString, TCanvas *>::iterator it = object_map.begin(); it != object_map.end(); ++it){
    object_map[it -> first] -> cd(cd_pad);
    object -> Draw(option);
  }

}

void TCanvasPool::Save(const char* file_type){
  for (map<TString, TCanvas *>::iterator it = object_map.begin(); it != object_map.end(); ++it){
    TString file_name = gspyOutputArea + "spy_plots/" + gsubArea + it -> first + "." + TString(file_type); 
    object_map[it -> first] -> SaveAs(file_name);
  }
}

void TCanvasPool::cd(const int a){
    TCanvas_pool = this;
    cd_pad = a;
}

void TCanvasPool::SetLogy(){
  for (map<TString, TCanvas *>::iterator it = object_map.begin(); it != object_map.end(); ++it){
    object_map[it -> first] -> SetLogy();
  }
}

void TCanvasPool::Divide (const int a, const int b)const {
  for (map<TString, TCanvas *>::const_iterator it = object_map.cbegin(); it != object_map.cend(); ++it){
    object_map.at(it -> first) -> Divide(a ,b);
  }
}

void TCanvasPool::SetPad(const int pad_number, const char* name, const char* title, Double_t xlow, Double_t ylow, Double_t xup, Double_t yup) const{
   for (map<TString, TCanvas *>::const_iterator it = object_map.cbegin(); it != object_map.cend(); ++it){
     TPad *pad = (TPad*)object_map.at(it -> first) -> GetPad(pad_number);
     pad -> SetPad(name, title, xlow, ylow, xup, yup, kWhite);
  }
}

TCanvasPool::~TCanvasPool(){
  printf("Deconstructing TCanvasPool\n");
}
