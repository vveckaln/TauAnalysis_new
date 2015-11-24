#include "CERN_RTU/TauAnalysis/interface/MuScleFitCorrector.h"

//cf. https://twiki.cern.ch/twiki/bin/view/CMSPublic/MuScleFitCorrections2012  
MuScleFitCorrector *getMuonCorrector(TString baseDir,TString url)
{
  bool is7TeV(url.Contains("7TeV"));
  bool isData(url.Contains("Data"));
  bool is2012D(url.Contains("2012D"));
  TString fName("");
  if(is7TeV) return 0;
  if(!is7TeV && !isData) fName="MuScleFit_2012_MC_53X_smearReReco.txt";
  if(!is7TeV && isData)
    {
      if(is2012D) fName="MuScleFit_2012D_DATA_ReReco_53X.txt";
      else        fName="MuScleFit_2012ABC_DATA_ReReco_53X.txt";
    }
  fName=baseDir+"/"+fName;
  return new MuScleFitCorrector(fName);
}

