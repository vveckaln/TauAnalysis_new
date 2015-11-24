#include "TauAnalysis/interface/CombinedTHStackTH1D.hh"
#include "TList.h"

CombinedTHStackTH1D::CombinedTHStackTH1D()
{
  
}

TGraph * CombinedTHStackTH1D::CreateRatioGraph()
{
  const TH1 * thstack_sum_histogram = (TH1*)thstack -> GetStack() -> Last();
  const unsigned int length = th1d -> GetNbinsX();
  double y_axis[length]; 
  double x_axis[length];
  unsigned int number_graph_entries = 0;
  for (unsigned int ind = 0; ind < length; ind ++)
    {
      const double bin_content1 = th1d -> GetBinContent(ind + 1);
      const double bin_content2 = thstack_sum_histogram -> GetBinContent(ind + 1);
      if (bin_content2 == 0) 
	continue;
      const double ratio = bin_content1/bin_content2;
      if (ratio > 5)
	continue;
      y_axis[number_graph_entries] = ratio; 
      x_axis[number_graph_entries] = ind + 0.5;
      number_graph_entries ++;
    }
  
  TGraph * graph = new TGraph(number_graph_entries, x_axis, y_axis);
  if (th1d -> GetXaxis() -> GetLabels())
    {
      graph -> GetXaxis() -> Set(length, 0, length);
      graph -> GetYaxis()->SetTitle("Data/#SigmaMC");
      for (unsigned int ind = 0; ind < length; ind ++)
	{
	  graph -> GetXaxis() -> SetBinLabel(ind + 1, th1d -> GetXaxis() -> GetBinLabel(ind + 1)); 
	}
    }
  
  graph -> SetMinimum(0.5);
  graph -> SetMaximum(1.5);
  graph -> SetMarkerStyle(21);
  return graph;
}

TCanvas * CombinedTHStackTH1D::ProduceDrawing()
{
  TCanvas * canvas = new TCanvas(thstack -> GetName(), thstack -> GetName());
  canvas -> Divide(1,2);
  canvas -> GetPad(1) -> SetPad("results", "results", 0, 0.31, 1, 1, kWhite);
  canvas -> GetPad(2) -> SetPad("ratio_graph", "ratio_graph", 0, 0, 1, 0.3, kWhite);
  canvas -> cd(1);
  if (thstack)
    thstack -> Draw();
  if (th1d)
    {
      th1d -> SetMarkerStyle(21);
      th1d -> Draw(thstack ? "SAMEp" : "p");
      canvas -> GetPad(1) -> SetLogy();
    }
  if (legend)
    legend -> Draw("SAME");
  canvas -> cd(2);
  if (graph)
    {
      graph -> Draw("AP");
      canvas -> GetPad(2) -> SetGrid();
    }

  return canvas;
}

TLegend * CombinedTHStackTH1D::UpdateLegend()
{
  if (not legend) 
    return NULL;
  legend -> AddEntry(th1d, "data", "p");
  return legend;
}

Int_t CombinedTHStackTH1D::Write(const char* name, Int_t option, Int_t bufsize)
{
  printf("writing\n");
  if (canvas)
    canvas -> Write();
  if (graph)
    graph -> Write();
  if (th1d)
    th1d -> Write();
  if (thstack)
    thstack -> Write();
  return 0;
}

CombinedTHStackTH1D::~ CombinedTHStackTH1D()
{
}
