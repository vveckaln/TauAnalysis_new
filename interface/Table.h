#ifndef _Table_hh
#define _Table_hh
#include <iostream>
#include <map>
#include "TString.h"
#include "TH1D.h"
#include "TNamed.h"
using namespace std;
class Column: public TObject
{
protected:
  TString columntitle;
  TString columnformat;
  
public:
  Column() {};
  const char * GetTitle() const {return columntitle;};
  virtual unsigned long size() const {return 0;};
  virtual void ls(const unsigned int ind) const {};
  virtual void Write(FILE *&, const unsigned int ind) const {};
  Column(const TString & title) : columntitle(title){};
  
  virtual  ~Column(){};
  ClassDef(Column, 1);
};

template<typename T>
class Column_spec : public Column
{
  vector<T> data;
public:
  Column_spec();
  virtual unsigned long size() const {return data.size();};
  
  Column_spec(const TString &title) : Column(title){};
  T & operator[](const unsigned int ind)
  {
    return data[ind];
  }
  void push_back(const T & t)
  {
    data.push_back(t);
  }
  /*void ls<struct T> (const uint ind) const
  {
    cout<<" omitted ";
    }*/
  virtual void ls(const unsigned int ind) const;
  virtual void Write(FILE *&, const unsigned int) const;

  virtual  ~Column_spec() { };
  ClassDef(Column_spec, 1);
};

template<typename T>
Column_spec<T>::Column_spec()
{
}

template<typename T>
void Column_spec<T>::ls(const unsigned int ind) const
  {
    cout<<"  "<< data[ind] <<"  ";
  }

template<typename T>
void Column_spec<T>::Write(FILE *&, const unsigned int ind) const {}




class Table : public TNamed
 
{
  vector<Column*> columns;
public:
  Table(const char* = "", const char* = "");
  template<typename T>
  void AddColumn(const TString & title= "")
  {
    columns.push_back(new Column_spec<T>(title));
  };
  template<typename T>
  void push_back(const unsigned int column, const T & t )
  {
    ((Column_spec<T>*)columns[column]) -> push_back(t);
    };
  
  void FillFromLabeledHistogram(const TH1D * histogram);
  void Save(const char * = "") const;
  void ls() const;
  ~Table();
  ClassDef(Table, 1);
};
//#include "LIP/TauAnalysis/interface/templates/Table.cpp"
#endif
