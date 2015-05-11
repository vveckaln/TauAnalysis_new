#include "LIP/TauAnalysis/interface/Parser.hh"

using namespace std;
using namespace parserHashes;

Parser::Parser()
{
  xml = new TXMLEngine();
}

vector <TString>* Parser::Parse(const char * input_xml_file)
{
  vector<TString> *output_vector = new vector<TString>;
  XMLDocPointer_t xmldoc = xml -> ParseFile(input_xml_file);
  if (xmldoc == NULL) 
    {
      printf("Error: parsing problem with file %s\n", input_xml_file);
      return NULL;
    }
  XMLNodePointer_t mainnode = xml -> DocGetRootElement(xmldoc);
  XMLNodePointer_t processnode = xml -> GetChild(mainnode);
  while (processnode != NULL)
    {
      TString nodename = xml -> GetNodeName(processnode);
      if (nodename == TString("process"))
	{
	   const TString file_name = ProcessChild(processnode);
	   output_vector -> push_back(file_name);
	}
      processnode = xml -> GetNext(processnode);
    }
  return output_vector;
}

vector<DataSampleDescriptor>* Parser::ParseDataSampleDescriptor(const char* histogram_specifier_xml)
{
  LoadColors();
  LoadStyles();
  vector<DataSampleDescriptor> *output_vector = new vector<DataSampleDescriptor>;
  XMLDocPointer_t xmldoc = xml -> ParseFile(histogram_specifier_xml);
  if (xmldoc == NULL) 
    {
      printf("Error: parsing problem with file %s\n", histogram_specifier_xml);
      return NULL;
    }
  XMLNodePointer_t mainnode = xml -> DocGetRootElement(xmldoc);
  XMLNodePointer_t processnode = xml -> GetChild(mainnode);
  while (processnode != NULL)
    {
      TString nodename = xml -> GetNodeName(processnode);
      if (nodename == TString("data_samples"))
	{
	  DataSampleDescriptor datasample_descriptor;
	  datasample_descriptor. datasample_identifier = xml -> GetNodeContent(processnode);
	  XMLAttrPointer_t attr = xml->GetFirstAttr(processnode);
	  while (attr)
	    {
	      TString attrName( xml->GetAttrName(attr));
	      if     (attrName == "HistogramFillHue") 
		datasample_descriptor.basic_hue      = GetColor(xml -> GetAttrValue(attr));
		  
	      else if     (attrName == "MarkerStyle") 
		datasample_descriptor.marker_style      =
		  TString(xml -> GetAttrValue(attr)) . IsDigit() ? 
		  atoi(xml -> GetAttrValue(attr)) : 
		  style_map[xml -> GetAttrValue(attr)];
	      else if(attrName == "HistogramFillHueAdjustment")
		datasample_descriptor.hue_adjustment = atoi(xml -> GetAttrValue(attr));
	      else if(attrName == "LegendEntry") 
		datasample_descriptor.legend_entry    = xml -> GetAttrValue(attr);
	      attr = xml->GetNextAttr(attr);
	    }
	  output_vector -> push_back(datasample_descriptor);
	}
      processnode = xml -> GetNext(processnode);
    }
  return output_vector;
}

vector<HistogramDescriptor>* Parser::ParseHistogramSpecifier(const char* histogram_specifier_xml)
{
  vector<HistogramDescriptor> *output_vector = new vector<HistogramDescriptor>;
  XMLDocPointer_t xmldoc = xml -> ParseFile(histogram_specifier_xml);
  if (xmldoc == NULL) 
    {
      printf("Error: parsing problem with file %s\n", histogram_specifier_xml);
      return NULL;
    }
  XMLNodePointer_t mainnode = xml -> DocGetRootElement(xmldoc);
  XMLNodePointer_t processnode = xml -> GetChild(mainnode);
  while (processnode != NULL)
    {
      TString nodename = xml -> GetNodeName(processnode);
      if (nodename == TString("histogram"))
	{
	  HistogramDescriptor histogram_descriptor;
	  histogram_descriptor. histogram_name = xml -> GetNodeContent(processnode);
	  XMLAttrPointer_t attr = xml->GetFirstAttr(processnode);
	  while (attr)
	    {
	      TString attrName( xml->GetAttrName(attr));
	      if     (attrName == "Xaxis_title") histogram_descriptor.Xaxis_title =       xml -> GetAttrValue(attr) ;
	      else if(attrName == "Yaxis_title") histogram_descriptor.Yaxis_title =       xml -> GetAttrValue(attr) ;
	      else if(attrName == "title")       histogram_descriptor.histogram_title =   xml -> GetAttrValue(attr) ;
	      else if(attrName == "nbinsx")      histogram_descriptor.nbinsx      = atoi( xml -> GetAttrValue(attr));
	      else if(attrName == "xlow")        histogram_descriptor.xlow        = atof( xml -> GetAttrValue(attr));
	      else if(attrName == "xup")         histogram_descriptor.xup         = atof( xml -> GetAttrValue(attr));
	      attr = xml->GetNextAttr(attr);
	    }
	  output_vector -> push_back(histogram_descriptor);
	}
      processnode = xml -> GetNext(processnode);
    }
  return output_vector;
}

HStructure * Parser::CreateHierarchicalStructure(const char* specifier)
{
  
  LoadColors();
  XMLDocPointer_t xmldoc = xml -> ParseFile(specifier);
  if (xmldoc == NULL) 
    {
      printf("Error: parsing problem with file %s\n", specifier);
      return NULL;
    }
  XMLNodePointer_t mainnode = xml -> DocGetRootElement(xmldoc);
  XMLNodePointer_t processnode = xml -> GetChild(mainnode);
  dynamic_structure * dyn_previous = NULL;
  while (processnode)
    {
      TString nodename = xml -> GetNodeName(processnode);
      if (nodename == TString("sample"))
	{
	  dynamic_structure * dyn = new dynamic_structure();
	  dyn -> previous = dyn_previous;
	  if (dyn_previous) 
	    dyn_previous -> next = dyn;
	  dyn_previous = dyn;
	  dyn -> current -> sample_name = xml -> GetNodeContent(processnode);
	  XMLAttrPointer_t attr = xml->GetFirstAttr(processnode);
	  while (attr)
	    {
	      TString attrName( xml->GetAttrName(attr));
	      if     (attrName == "sample_title") 
		dyn -> current -> sample_title =       xml -> GetAttrValue(attr) ;
	      else if(attrName == "color")        
		dyn -> current -> fill_color        =GetColor(xml -> GetAttrValue(attr)) ;
	      else if(attrName == "id")           
		dyn -> current -> ID           =       xml -> GetAttrValue(attr) ;
	      else if(attrName == "marker_style")       
		dyn -> current -> marker_style       =GetStyle(xml -> GetAttrValue(attr)) ;

	      attr = xml->GetNextAttr(attr);
	    }
	}
      processnode = xml -> GetNext(processnode);
    }
  dynamic_structure * end = dyn_previous;
  dynamic_structure * analysed_structure = end;
  dynamic_structure * test = end;
  while(test)
    {
      test = test -> previous;
    }
  while(analysed_structure)
    {
      const char* parent = analysed_structure -> current -> GetParent();
      dynamic_structure * searcher = end;
      if (TString(parent) != "0")
	{
	  while(searcher)
	    {
	      if (TString(searcher -> current -> ID) == parent)
		{
		  searcher -> current -> children.push_back(analysed_structure -> current);
		  analysed_structure -> current -> parent = searcher -> current;
		}
	      searcher = searcher -> previous;
	  
	    }
	}
      analysed_structure = analysed_structure -> previous;
      delete [] parent;
    }
  HStructure * top_structure = NULL;
  dynamic_structure * deletor = end;
  do 
    {
      if (not deletor -> previous) 
	top_structure = deletor -> current;
      dynamic_structure * scheduled = deletor;
      deletor = deletor -> previous;
      delete scheduled;
    } while(deletor);
  return top_structure;
}

const char* Parser::ProcessChild(XMLNodePointer_t processnode)
{
  XMLNodePointer_t child = xml -> GetChild(processnode);
  TString childname = xml -> GetNodeName(child);
  return xml -> GetNodeContent(child);
  
}

void Parser::LoadColors()
{
  for (unsigned char ind = 0; ind < color_size; ind ++)
    {
      color_map[color_TString[ind]] = color_hash[ind];
    }
}
void Parser::LoadStyles()
{
  for (unsigned char ind = 0; ind < style_size; ind ++)
    {
      style_map[style_TString[ind]] = style_hash[ind];
    }
}

Color_t Parser::GetColor(const char * attr_value) const
{
  return TString(attr_value) . IsDigit() ? 
    atoi(attr_value) : 
    color_map.at(TString(attr_value));
}

Style_t Parser::GetStyle(const char * attr_value) const
{
  return TString(attr_value) . IsDigit() ? 
    atoi(attr_value) : 
    style_map.at(TString(attr_value));
}

Parser::~Parser()
{
  delete xml;
}

dynamic_structure::dynamic_structure()
{
  current = new HStructure();
};
