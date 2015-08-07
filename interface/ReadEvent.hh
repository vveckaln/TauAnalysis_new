#ifndef _ReadEvent_hh
#define _ReadEvent_hh

#include "LIP/TauAnalysis/interface/Event.hh"
#include "TTree.h"
#include "TClonesArray.h"

class ReadEvent: public Event
{
public:
  int iRun;
  int iEvent;
  int iLumi;
  TClonesArray *eventClassif;
  TClonesArray *triggerColl;
  TClonesArray *vertexColl;
  TClonesArray *leptonsColl;
  TClonesArray *leptonsClassifColl;
  TClonesArray *photonsColl;
  TClonesArray *photonsClassifColl;
  TClonesArray *jetsColl;
  TClonesArray *jetsClassifColl;
  TClonesArray *metColl;
  TClonesArray *metClassifColl;
  TClonesArray *quarksColl;
  TClonesArray *quarksClassifColl;
  void ConnectToTree(TTree *);
  ReadEvent operator=(const ReadEvent & other);
  ReadEvent();
  void Open();
  void Close();
  ~ReadEvent(){};
} ;
#endif
