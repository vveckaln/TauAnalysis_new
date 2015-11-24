#ifndef _Parser_hh
#define _Parser_hh

#include <vector>
#include <map>
#include "TauAnalysis/interface/HistogramDescriptor.hh"
#include "TauAnalysis/interface/DataSampleDescriptor.hh"
#include "TauAnalysis/interface/ParserHashes.hh"
#include "TauAnalysis/interface/HStructure.hh"

#include <TString.h>
#include "TXMLEngine.h" // needs '<flags LDFLAGS="-lXMLIO">' in the BuildFile

using namespace std;
using namespace parserHashes;

class Parser
{
protected:
  map<TString, Style_t> style_map;
  map<TString, Color_t> color_map;
  void LoadColors();
  void LoadStyles();
  TXMLEngine *xml;
  const char* ProcessChild(XMLNodePointer_t processnode);
public:
  Parser();
  vector <HistogramDescriptor>* ParseHistogramSpecifier(const char *);
  vector <DataSampleDescriptor>* ParseDataSampleDescriptor(const char *);
  HStructure * CreateHierarchicalStructure(const char*);

  vector <TString>* Parse(const char * input_xml_file);
  ~Parser();
  
  Color_t GetColor(const char* ) const;
  Style_t GetStyle(const char* ) const;
};
struct dynamic_structure
{
  dynamic_structure();

  HStructure *current;
  dynamic_structure *previous;
  dynamic_structure *next;
};
#endif
