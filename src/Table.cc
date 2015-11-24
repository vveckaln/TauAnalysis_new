#include "TauAnalysis/interface/Table.h"
ClassImp(Column_spec<short>);
ClassImp(Column_spec<const char *>);
ClassImp(Column_spec<TString>);

ClassImp(Column_spec<unsigned short>);
ClassImp(Column_spec<float>);
ClassImp(Column_spec<double>);

ClassImp(Column);
ClassImp(Table);

using namespace std;

template<>
void Column_spec<const char*>::ls(const uint ind) const
{
  printf(" %20s ", data[ind]);
}

template<>
void Column_spec<TString>::ls(const uint ind) const
{
  printf(" %20s ", data[ind].Data());
}

template<>
void Column_spec<const char*>::Write(FILE *&file, const uint ind)  const
{
  fprintf(file, " %20s ", data[ind]);
}

template<>
void Column_spec<TString>::Write(FILE *&file, const uint ind)  const
{
  fprintf(file, " %20s ", data[ind].Data());
}

template<>
void Column_spec<short>::Write(FILE *&file, const uint ind) const
{
  fprintf(file, " %d ", data[ind]);
}
template<>
void Column_spec<unsigned short>::Write(FILE *&file, const uint ind) const
{
  fprintf(file, " %u ", data[ind]);
}
template<>
void Column_spec<float>::Write(FILE *&file, const uint ind) const
{
  fprintf(file, " %f ", data[ind]);
}

template<>
void Column_spec<double>::Write(FILE *&file, const uint ind) const
{
  fprintf(file, " %f ", data[ind]);
}

Table::Table(const char * title, const char* name): TNamed(title, name)
{

}

void Table::FillFromLabeledHistogram(const TH1D * histogram)
{
  AddColumn<unsigned short>      ("Number");
  AddColumn<TString>             ("Entry");
  AddColumn<double>              ("Count");
   for (ushort bin_ind = 1; bin_ind <= histogram -> GetNbinsX(); bin_ind++)
    {
      push_back(0, bin_ind);
      push_back(1, TString(histogram -> GetXaxis() -> GetBinLabel(bin_ind)));
      push_back(2, histogram -> GetBinContent(bin_ind));
    }
 }

void Table::Save(const char * address) const
{
  TString file_address = TString(address) == "" ? TString(GetTitle()) + ".txt" : TString(address);
  FILE * file = fopen(file_address.Data(), "w");
  for (uint row_ind = 0; row_ind < columns[0] -> size(); row_ind ++)
    {
      for (uint col_ind = 0; col_ind < columns. size(); col_ind ++)
	{
    	  columns[col_ind] -> Write(file, row_ind);
	}
    fprintf(file, "\n");
    }
  fflush(file);
  fclose(file);
}

void Table::ls() const
{
  for (uint col_ind = 0; col_ind < columns. size(); col_ind ++)
    {
      printf("%s   ", columns[col_ind] -> GetTitle());
    }
  printf("\n");
  for (uint row_ind = 0; row_ind < columns[0] -> size(); row_ind ++)
    {
      for (uint col_ind = 0; col_ind < columns. size(); col_ind ++)
	{
    	  columns[col_ind] -> ls(row_ind);
	}
      printf("\n");
    }

  printf("---- end -----\n");
}

Table::~Table()
{
  for (uint ind = 0; ind < columns.size(); ind ++)
    {
      delete columns[ind];
    }
}
