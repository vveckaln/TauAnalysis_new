#include "LIP/TauAnalysis/interface/CombinedTHStackTH1DPool.hh"

using namespace std;

CombinedTHStackTH1DPool::CombinedTHStackTH1DPool()
{
}

void CombinedTHStackTH1DPool::Process()
{
  
  for (it = object_map.begin(); it != object_map.end(); ++it)
    {
      it -> second -> UpdateLegend(); 
      it -> second -> graph = it -> second -> CreateRatioGraph();
      it -> second -> canvas = it -> second -> ProduceDrawing();
    } 
}
CombinedTHStackTH1DPool::~CombinedTHStackTH1DPool()
{
}

