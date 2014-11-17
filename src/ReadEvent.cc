#include "LIP/TauAnalysis/interface/ReadEvent.hh"
void ReadEvent::ConnectToTree(TTree *spy_tree){
  spy_tree -> GetBranch("RunNb")               -> SetAddress( & iRun);
  spy_tree -> GetBranch("EventNb")             -> SetAddress( & iEvent);
  spy_tree -> GetBranch("Lumi")                -> SetAddress( & iLumi);
  spy_tree -> GetBranch("EventClassification") -> SetAddress( & eventClassif);
  spy_tree -> GetBranch("Trigger")             -> SetAddress( & triggerColl);
  spy_tree -> GetBranch("Vertices")            -> SetAddress( & vertexColl);
  spy_tree -> GetBranch("Leptons")             -> SetAddress( & leptonsColl);
  spy_tree -> GetBranch("LeptonInfo")          -> SetAddress( & leptonsClassifColl);
  spy_tree -> GetBranch("Photons")             -> SetAddress( & photonsColl);
  spy_tree -> GetBranch("PhotonsInfo")         -> SetAddress( & photonsClassifColl);
  spy_tree -> GetBranch("Jets")                -> SetAddress( & jetsColl);
  spy_tree -> GetBranch("JetsInfo")            -> SetAddress( & jetsClassifColl);
  spy_tree -> GetBranch("MET")                 -> SetAddress( & metColl);
  spy_tree -> GetBranch("METInfo")             -> SetAddress( & metClassifColl);
}

ReadEvent ReadEvent::operator=(const ReadEvent & other){
  eventClassif       = new TClonesArray(*other . eventClassif);
  triggerColl        = new TClonesArray(*other . triggerColl);
  vertexColl         = new TClonesArray(*other . vertexColl);
  leptonsColl        = new TClonesArray(*other . leptonsColl);
  leptonsClassifColl = new TClonesArray(*other . leptonsClassifColl);
  photonsColl        = new TClonesArray(*other . photonsColl);
  photonsClassifColl = new TClonesArray(*other . photonsClassifColl);
  jetsColl           = new TClonesArray(*other . jetsColl);
  jetsClassifColl    = new TClonesArray(*other . jetsClassifColl);
  metColl            = new TClonesArray(*other . metColl);
  metClassifColl     = new TClonesArray(*other . metClassifColl);
  quarksColl         = new TClonesArray(*other . quarksColl);
  quarksClassifColl  = new TClonesArray(*other . quarksClassifColl);
  return *this;

}

ReadEvent::ReadEvent(){
  iRun =   0;
  iEvent = 0;
  iLumi =  0;
  eventClassif       = NULL;
  triggerColl        = NULL;
  vertexColl         = NULL;
  leptonsColl        = NULL;
  leptonsClassifColl = NULL;
  photonsColl        = NULL;
  photonsClassifColl = NULL;
  jetsColl           = NULL;
  jetsClassifColl    = NULL;
  metColl            = NULL;
  metClassifColl     = NULL;
  quarksColl         = NULL;
  quarksClassifColl  = NULL;

}

void ReadEvent::Open(){
  eventClassif       = new TClonesArray();
  triggerColl        = new TClonesArray();
  vertexColl         = new TClonesArray();
  leptonsColl        = new TClonesArray();
  leptonsClassifColl = new TClonesArray();
  photonsColl        = new TClonesArray();
  photonsClassifColl = new TClonesArray();
  jetsColl           = new TClonesArray();
  jetsClassifColl    = new TClonesArray();
  metColl            = new TClonesArray();
  metClassifColl     = new TClonesArray();
  quarksColl         = new TClonesArray();
  quarksClassifColl  = new TClonesArray();

}

void ReadEvent::Close(){
  eventClassif -> Clear();
  delete eventClassif       ;
  triggerColl -> Clear();
  delete triggerColl        ;
  vertexColl -> Clear();
  delete vertexColl         ;
  leptonsColl -> Clear();
  delete leptonsColl        ;
  leptonsClassifColl -> Clear();
  delete leptonsClassifColl ;
  photonsColl -> Clear();
  delete photonsColl        ;
  photonsClassifColl -> Clear();
  delete photonsClassifColl ;
  jetsColl -> Clear();
  delete jetsColl           ;
  jetsClassifColl -> Clear();
  delete jetsClassifColl    ;
  metColl -> Clear();
  delete metColl            ;
  metClassifColl -> Clear();
  delete metClassifColl     ;
  quarksColl -> Clear();
  delete quarksColl         ;
  quarksClassifColl -> Clear();
  delete quarksClassifColl  ;

}

/*ReadEvent::~ReadEvent(){
  printf("invoking ~ReadEvent()\n");
  delete leptonsColl        ;
  delete leptonsClassifColl ;
}
*/
