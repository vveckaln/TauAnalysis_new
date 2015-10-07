#include "LIP/TauAnalysis/interface/TGraphPool.hh"
#include "LIP/TauAnalysis/interface/Parser.hh"
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"
#include "LIP/TauAnalysis/interface/GlobalVariables.hh"
#include "LIP/TauAnalysis/interface/CPFileRegister.hh"
#include <stdlib.h>
#include <stdio.h>
using namespace std;
using namespace gVariables;

TGraphPool::TGraphPool(){
}



void TGraphPool::ConstructRatioGraphs(HistogramPool *hpool1, HistogramPool *hpool2){
  for (map<TString, TH1D*>::iterator it = hpool1 -> object_map.begin(); it != hpool1 -> object_map.end(); it ++){
    unsigned int length = hpool1->operator[](it -> first) -> GetNbinsX();
    vector<double> xaxis_vector, yaxis_vector;
    for (unsigned char ind = 0; ind < length; ind ++){
      double bin_content1 = hpool1 -> operator[](it -> first) -> GetBinContent(ind + 1);
      double bin_content2 = hpool2 -> operator[](it -> first) -> GetBinContent(ind + 1);
      if (bin_content1 < 5 || bin_content2 < 5) continue;
      xaxis_vector . push_back(hpool1 -> operator[](it -> first) -> GetBinCenter(ind + 1));
      double ratio = bin_content1/bin_content2;
      yaxis_vector . push_back(ratio);
      //printf("%f %f %f %f\n", ratio, bin_content1, bin_content2, hpool1 -> operator[](it -> first) -> GetBinCenter(ind + 1));
    }
    double xaxis[yaxis_vector . size()], yaxis[yaxis_vector . size()];
    for (unsigned char ind = 0; ind < yaxis_vector . size(); ind ++){
      xaxis[ind] = xaxis_vector[ind];
      yaxis[ind] = yaxis_vector[ind];
    }
    object_map[it -> first] = new TGraph(xaxis_vector . size(), xaxis, yaxis);
    object_map[it -> first] -> GetXaxis() -> SetLimits(hpool1 -> operator[](it -> first) -> GetBinCenter(1), hpool1 -> operator[](it -> first) -> GetBinCenter(length));
  }
}

TGraphPool::~TGraphPool(){
}

