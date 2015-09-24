#ifdef __CINT__
 
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;
 
//#pragma link C++ defined_in "interface/Table.h";
#pragma link C++ class Column_spec<float>+;
#pragma link C++ class Column_spec<short>+;
#pragma link C++ class Column_spec<double>+;
#pragma link C++ class Column_spec<unsigned short>+;
#pragma link C++ class Column_spec<const char*>+;
#pragma link C++ class Column_spec<TString>+;
#pragma link C++ class Column+;
#pragma link C++ class Table+;

#endif
