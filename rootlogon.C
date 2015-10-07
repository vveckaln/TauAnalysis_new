#include <stdlib.h>
#include <string>
void rootlogon()
{
  const char * HOST = getenv("HOSTNAME");
  const string HOSTstr(HOST);
  std::size_t find = HOSTstr.find("ncg.ingrid.pt");
  if (find != std::string::npos)
    cout<<"running logon file /exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_7_4_2/src/LIP/TauAnalysis/rootlogon.C called from ~/.rootrc"<<endl;
  else
    cout<<"running logon file /afs/cern.ch/work/v/vveckaln/private/CMSSW_7_4_2/src/LIP/TauAnalysis/rootlogon.C called from ~/.rootrc"<<endl;
  gSystem->Load( "libFWCoreFWLite.so" );
  gSystem->Load( "libLIPTauAnalysis.so" );
  cout<<"ROOT configuration completed"<<endl;
}

