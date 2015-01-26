#include "LIP/TauAnalysis/interface/HistogramPool.hh"
#include "LIP/TauAnalysis/interface/Parser.hh"
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
#include <stdlib.h>
#include <stdio.h>
using namespace std;
using namespace gVariables;
unsigned int HistogramPool::instances = 0;

HistogramPool::HistogramPool()
{
  printf("Default HistogramPool constructor\n");
  processed_event = NULL;
  histogram_map = &object_map;
  instances ++;
}

HistogramPool::HistogramPool(const vector<HistogramDescriptor> * object_descriptors, const char * title, const char* is_temporary)
{
  this -> title = title;
  instances ++;
  processed_event = NULL;
  char str[4];
  sprintf(str, "%u", instances);
  TString append = str;
  temporary = (TString(is_temporary) == "temporary") ? true : false;

  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++)
    {
    
      TString histogram_title = (temporary) ?
	object_descriptors -> at(obj_ind).histogram_title + append :
	object_descriptors -> at(obj_ind).histogram_title;
      TH1D *obj = new TH1D (
			    histogram_title + this -> title, 
			    object_descriptors -> at(obj_ind).histogram_title,
			    object_descriptors -> at(obj_ind).nbinsx,
			    object_descriptors -> at(obj_ind).xlow,
			    object_descriptors -> at(obj_ind).xup
			    );
      TAxis *xaxis = obj -> GetXaxis();
      xaxis -> SetTitle(object_descriptors -> at(obj_ind) . Xaxis_title);
      TAxis *yaxis = obj -> GetYaxis();
      yaxis -> SetTitle(object_descriptors -> at(obj_ind) . Yaxis_title);
      object_map[object_descriptors -> at(obj_ind).histogram_title] = obj;
    } 
  histogram_map = &object_map;
}

void HistogramPool::SetTitle(const char * directory_title)
{
  this -> directory_title = directory_title;
}

void HistogramPool::AddObjects(const vector<HistogramDescriptor> * object_descriptors)
{
  char str[4];
  sprintf(str, "%u", instances);
  TString append = str;
  for (unsigned char obj_ind = 0; obj_ind < object_descriptors -> size(); obj_ind ++){
    
    TString title =  (temporary)?
      object_descriptors -> at(obj_ind).histogram_title + append :
      object_descriptors -> at(obj_ind).histogram_title;
    TH1D *obj = new TH1D (
			  title, 
			  object_descriptors -> at(obj_ind).histogram_title,
			  object_descriptors -> at(obj_ind).nbinsx,
			  object_descriptors -> at(obj_ind).xlow,
			  object_descriptors -> at(obj_ind).xup
			  );
    TAxis *xaxis = obj -> GetXaxis();
    xaxis -> SetTitle(object_descriptors -> at(obj_ind) . Xaxis_title);
    TAxis *yaxis = obj -> GetYaxis();
    yaxis -> SetTitle(object_descriptors -> at(obj_ind) . Yaxis_title);
    object_map[object_descriptors -> at(obj_ind).histogram_title] = obj;
  } 
}

void HistogramPool::Fill_Delta_R_lepton_1st_leading_jet()
{
  const double Delta_R = processed_event -> lepton. DeltaR
    (*processed_event -> GetLeadingJet("Pt", 1));
  (*histogram_map)["Delta_R_lepton_1st_leading_jet"] -> Fill(Delta_R);
 
}

void HistogramPool::Fill_Abs_Delta_phi_lepton_MET()
{
  const Lepton * lepton = &processed_event -> lepton;
  const double Abs_Delta_phi = fabs(lepton -> DeltaPhi(processed_event -> met));
  (*histogram_map)["Abs_Delta_phi_lepton_MET"] -> Fill(Abs_Delta_phi);
 
}

void HistogramPool::Fill_eta_tau()
{
  const double eta_tau = processed_event -> tau . Eta();
  (*histogram_map)["eta_tau"] -> Fill(eta_tau);
 
}

void HistogramPool::AddEntryToLegend(TLegend *& legend, const char* label, Option_t* option)
{
  it = histogram_map -> begin();
  legend -> AddEntry(it -> second, label, option);
}

void HistogramPool::Normalise(HistogramPool *other)
{
  
  for (it = object_map.begin(); it != object_map.end(); ++it){
    const double ratio = other -> object_map . at(it -> first) -> Integral()/it-> second -> Integral();
    it -> second -> Scale(ratio);
  }
}

HistogramPool::~HistogramPool()
{
  printf("Deconstructing histogrampool\n");
}

