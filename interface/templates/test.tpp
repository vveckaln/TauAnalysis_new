#include "CERN_RTU/TauAnalysis/interface/ObjectPool.hh"
using namespace cpHistogramPoolRegister;
template<class Object>
void ObjectPool<Object>::Draw(Option_t * draw_option){
  for (typename map<TString, Object*>::iterator it = object_map.begin(); it != object_map.end(); ++it){
    TCanvas_pool -> at(it -> first) -> cd(TCanvas_pool -> cd_pad);
    it -> second -> Draw(draw_option);
    gPad -> Modified();
    gPad -> Update();
  } 
}