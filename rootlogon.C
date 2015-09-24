void rootlogon()
{
  cout<<"running logon file /afs/cern.ch/work/v/vveckaln/private/CMSSW_7_4_2/src/LIP/TauAnalysis/rootlogon.C called from ~/.rootrc"<<endl;
  gSystem->Load( "libFWCoreFWLite.so" );
  gSystem->Load( "libLIPTauAnalysis.so" );
  cout<<"ROOT configuration completed"<<endl;
}

