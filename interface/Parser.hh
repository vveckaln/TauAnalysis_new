#ifndef _Parser_hh
#define _Parser_hh

#include <vector>
#include <map>
#include "LIP/TauAnalysis/interface/HistogramDescriptor.hh"
#include "LIP/TauAnalysis/interface/DataSampleDescriptor.hh"
#include "LIP/TauAnalysis/interface/ParserHashes.hh"
#include <TString.h>
#include "TXMLEngine.h" // needs '<flags LDFLAGS="-lXMLIO">' in the BuildFile

using namespace std;
using namespace parserHashes;

class Parser
{
public:
  Parser();
  vector <HistogramDescriptor>* ParseHistogramSpecifier(const char *);
  vector <DataSampleDescriptor>* ParseDataSampleDescriptor(const char *);
  vector <TString>* Parse(const char * input_xml_file);
  ~Parser();
  void LoadColors();
  void LoadStyles();
protected:
  map<TString, Style_t> style_map;
  map<TString, Color_t> color_map;
  TXMLEngine *xml;
  const char* ProcessChild(XMLNodePointer_t processnode);
  

};
#endif
