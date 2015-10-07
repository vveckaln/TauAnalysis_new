#include "LIP/TauAnalysis/interface/TFilePool.hh"

using namespace std;

TFilePool::TFilePool()
{
}

TFilePool::TFilePool(const vector<string> & file_names, const Option_t * option)
{
  for (uint file_ind = 0; file_ind < file_names.size(); file_ind ++)
    {
      object_map[file_names[file_ind].c_str()] = new  TFile(file_names[file_ind].c_str(), option);
    }
}

TFilePool::TFilePool(const vector<TString> & file_names, const Option_t * option)
{
  for (uint file_ind = 0; file_ind < file_names.size(); file_ind ++)
    {
      object_map[file_names[file_ind]] = new  TFile(file_names[file_ind], option);
    }
}

void TFilePool::Close()
{
  for (map<TString, TFile*>::const_iterator cit = object_map.cbegin(); cit != object_map.cend(); cit ++)
    {
      if (cit -> second != NULL) cit -> second -> Close();
    }
}

TFilePool::~TFilePool()
{
}

