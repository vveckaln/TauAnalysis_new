#include "lipcms/EventSelection/interface/GenTopEvent.hh"
#include "DataFormats/Math/interface/deltaR.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

using namespace std;

namespace gen
{
  namespace top
  {
     
    //
    const reco::Candidate *Event::findFirstMotherOf(const reco::Candidate *p)
    {
      if(p==0) return 0;
      const reco::Candidate *nextP = p->mother();
      if(nextP==0) return 0;
      int pdgId = p->pdgId();
      int motherPdgId = nextP->pdgId();
      int iTry(0);
      while(pdgId==motherPdgId)
	{
	  iTry++;
	  nextP = nextP->mother();
	  if(nextP==0) return 0;
	  motherPdgId = nextP->pdgId();
	  if(iTry>10) return 0;
	}
      return nextP;
    }
      
    //
    const reco::Candidate *Event::getFinalStateFor(const reco::Candidate *p)
    {
      if(p==0) return 0;
	
      const reco::Candidate *prevState=p;
      do{	
	const reco::Candidate *nextState=0;
	int nDaughters = prevState->numberOfDaughters();
	for(int iDaughter=0; iDaughter<nDaughters; iDaughter++)
	  {
	    const reco::Candidate *dau = prevState->daughter(iDaughter);
	    if(dau==0) continue;
	    if(dau->pdgId()!= p->pdgId()) continue;
	    nextState=dau;	   
	    break;
	  }
	if(nextState==0) break;
	if(nextState==prevState) break;
	prevState=nextState;
      }while(1);
	
      return prevState;
    }
      
      
    //
    const reco::Candidate *Event::getCandidateFor(const reco::Candidate *recoCandidate, int id, double matchCone)
    {
      if(recoCandidate==0) return 0;
      std::list<const reco::Candidate *> &candList = (abs(id)>6 ? leptons : quarks );
	
      //find the closest candidate (compare also with the final state)
      double minDeltaR(100.);
      const reco::Candidate *matchCandidate=0;
      for(std::list<const reco::Candidate *>::iterator it = candList.begin();
	  it != candList.end();
	  it++)
	{
	  if(abs(id)>6 && TMath::Abs((*it)->pdgId()) != TMath::Abs(id)) continue;
	  const reco::Candidate * fs = getFinalStateFor( *it );
	  double dR = deltaR( **it, *recoCandidate );
	  double dR2 = deltaR( *fs, *recoCandidate );
	  if(dR>minDeltaR && dR2>minDeltaR) continue;
	  matchCandidate = *it;
	  minDeltaR=(dR<dR2 ? dR : dR2);
	}
	
      //return non null if found inside a reasonable match cone
      if(minDeltaR>matchCone) matchCandidate=0;
	
      return matchCandidate;
    }


    //
    const reco::Candidate *Event::getNearestCandidateFor(double eta, double phi, int id, double matchCone)
    {
      std::list<const reco::Candidate *> &candList = (abs(id)>6 ? leptons : quarks );
	
      //find the closest candidate (compare also with the final state)
      double minDeltaR(100.);
      const reco::Candidate *matchCandidate=0;
      for(std::list<const reco::Candidate *>::iterator it = candList.begin();
	  it != candList.end();
	  it++)
	{
	  if(abs(id)>6 && TMath::Abs((*it)->pdgId()) != TMath::Abs(id)) continue;
	  const reco::Candidate * fs = getFinalStateFor( *it );
	  double dR = deltaR( (*it)->eta(), (*it)->phi(), eta, phi );
	  double dR2 = deltaR( fs->eta(), fs->phi(), eta, phi );
	  if(dR>minDeltaR && dR2>minDeltaR) continue;
	  matchCandidate = *it;
	  minDeltaR=(dR<dR2 ? dR : dR2);
	}
      
      //return non null if found inside a reasonable match cone
      if(minDeltaR>matchCone) matchCandidate=0;
	
      return matchCandidate;
    }
      
    //
    const reco::Candidate *Event::getPartonCandidateForJet(const reco::Candidate *j)
    {
      if(j==0) return 0;
      std::map<const reco::Candidate *,const reco::Candidate *>::iterator pToJet= jetsToPartons.find(j);
      if(pToJet == jetsToPartons.end()) return 0;
      return pToJet->second;
    }

    //
    void Event::fillJetToPartonMap(const edm::Event& iEvent, const edm::EventSetup& iSetup, std::vector<edm::InputTag> *sources)
    {
      if(sources==0) return;
      jetsToPartons.clear();
      for(std::vector<edm::InputTag>::iterator sit = sources->begin();
	  sit != sources->end();
	  sit++)
	{
	  try{
	    edm::Handle<reco::JetMatchedPartonsCollection>  jetPartonMapper;
	    iEvent.getByLabel( *sit, jetPartonMapper );
	    if(!jetPartonMapper.isValid()) continue;
	    for( reco::JetMatchedPartonsCollection::const_iterator f  = jetPartonMapper->begin();
		 f != jetPartonMapper->end();
		 f++)
	      {
		  
		//the jet
		const edm::RefToBase<reco::Jet> matchedJet = f->first;
		if(matchedJet.isNull()) continue;
		  
		//get the parton match
		const reco::GenParticle *theParton = 0;	    
		try{
		  const reco::GenParticleRef algoParton = f->second.algoDefinitionParton();
		  if( !algoParton.isNull() )      theParton = &(*algoParton);
		  //if( theParton==0)
		  //  {
		  //    const reco::GenParticleRef physParton = f->second.physicsDefinitionParton();
		  //    if( !physParton.isNull() ) theParton = &(*physParton); 
		  //  }
		}catch(std::exception &e){
		}	      
		  
		//check if it is of interest and store
		if(theParton==0) continue;
		if( getCandidateFor(theParton,theParton->pdgId()) ==0 ) continue;
		jetsToPartons[&(*matchedJet)] = theParton;
	      }
	  }catch(std::exception &e){
	    cout << e.what() << endl;
	  }
	} 
    }
    
    //
    int Event::assignDYchannel(const edm::Event& iEvent, const edm::EventSetup& iSetup)
    {
      //retrieve the generator level particle collection      
      edm::Handle<reco::GenParticleCollection> genParticles;
      iEvent.getByLabel("genParticles", genParticles);
      int dyChannel=UNKNOWN;
      
      //iterate over the collection and store Z/gamma->ll decays
      dyDaughters.clear();
      for(size_t i = 0; i < genParticles->size(); ++ i) 
	{
	  const reco::GenParticle & p = (*genParticles)[i];
	  int id_p   = p.pdgId();   
	  //select Z
	  if(abs(id_p) != 23 && abs(id_p)!=22) continue;   
	  if( p.status()!=3) continue;
	  
	  int nElecs(0), nMuons(0), nTaus(0);
	  for(size_t b = 0; b < p.numberOfDaughters(); ++ b)
	    {
	      int id_d = abs (p.daughter(b)->pdgId());
	      if(id_d == 11) { nElecs++; dyDaughters.push_back( p.daughter(b) ); }
	      if(id_d == 13) { nMuons++; dyDaughters.push_back( p.daughter(b) ); }
	      if(id_d == 15) { nTaus++;  dyDaughters.push_back( p.daughter(b) ); }

	    }
	  if(nElecs>1) dyChannel=EE;
	  else if(nMuons>1) dyChannel=MUMU;
	  else if(nTaus>1) dyChannel=TAUTAU;
	}
      dyDaughters.sort(); dyDaughters.unique();
      return dyChannel;
    }

    //Code to disentangle Z+jets from Z ->tau tau 
    int Event::assignZJets(const edm::Event& iEvent, const edm::EventSetup& iSetup,std::vector<edm::InputTag> *jpsources){    
      
      //retrieve the generator level particle collection
      edm::Handle<reco::GenParticleCollection> genParticles;
      iEvent.getByLabel("genParticles", genParticles);
      ///////////////////////////////////////////////////

      tops.clear(); leptons.clear();  neutrinos.clear(); quarks.clear();     

      int dyChannel=UNKNOWN;	
      int ret = ZJETS;
      dyDaughters.clear();
      for(size_t i = 0; i < genParticles->size(); ++ i) {
	const reco::GenParticle & p = (*genParticles)[i];
	int id_p   = p.pdgId();
	if(abs(id_p) == 23){      //If we find a Z
	  int nTaus(0);
	  for(size_t b = 0; b < p.numberOfDaughters(); ++ b){
	    const reco::Candidate * w_daughter = p.daughter(b);
	    if(abs(w_daughter->pdgId()) == 15) {nTaus++; 
	      //need to find the hadronic decay taus
	      bool noLepton = true; 
	      for(size_t c = 0; c < w_daughter->numberOfDaughters(); ++ c){ 
		const reco::Candidate * Tau_daughter = w_daughter->daughter(c); 
		if(abs(Tau_daughter->pdgId()) == 15){
		  for(size_t d = 0; d < Tau_daughter->numberOfDaughters(); ++ d){ 
		    const reco::Candidate * Tau_daughter2 = Tau_daughter->daughter(d); 
		    int tausonid = abs(Tau_daughter2->pdgId()); 
		    if(tausonid == 11 || tausonid == 13)noLepton = false;
		    //some time tau decays to tau + gamma, or to virtual W, check one more loop
		    if(tausonid == 15 || tausonid == 24){
		      for(size_t e = 0; e < Tau_daughter2->numberOfDaughters(); ++ e){
			const reco::Candidate * Tau_daughter3 = Tau_daughter2->daughter(e);
			int tausonid2 = abs(Tau_daughter3->pdgId());
			if(tausonid2 == 11 || tausonid2 == 13)noLepton = false;
		      }
		    }
		  }
		}
		else if(abs(Tau_daughter->pdgId()) == 11)noLepton = false;
		else if(abs(Tau_daughter->pdgId()) == 13)noLepton = false;
	      }
	      if(noLepton)dyDaughters.push_back( p.daughter(b) );
	    }
	    if(abs(w_daughter->pdgId()) == 11 || abs(w_daughter->pdgId()) == 13){
	      dyDaughters.push_back( p.daughter(b));
	    }
	    if(nTaus > 0)ret = ZTAUTAU;
	  }
	}
      }
      return ret;
    }
    //Code to disentangle W+jets in enu, munu, taunu
    int Event::assignWJets(const edm::Event& iEvent, const edm::EventSetup& iSetup,std::vector<edm::InputTag> *jpsources){    
      
      //retrieve the generator level particle collection
      edm::Handle<reco::GenParticleCollection> genParticles;
      iEvent.getByLabel("genParticles", genParticles);
      ///////////////////////////////////////////////////
	
      //reset all
      int quarkCounter(0),chLeptonCounter(0),electronCounter(0),muonCounter(0),tauCounter(0);  
      tops.clear(); leptons.clear();  neutrinos.clear(); quarks.clear();
      dyDaughters.clear();

      for(size_t i = 0; i < genParticles->size(); ++ i) {
	
	
        const reco::GenParticle & p = (*genParticles)[i];
	
        int id_p   = p.pdgId();
        if( abs(id_p) == 24 ){      //If we find a W
	  
          for(size_t b = 0; b < p.numberOfDaughters(); ++ b){
            const reco::Candidate * Wson_i = p.daughter(b);
	    
	    int id_Wson = Wson_i->pdgId();
	    
	    //taus must be traced further
	    if(abs(id_Wson) == 15){	    	         
	      int tempLepton = 0;
	      for(size_t c = 0; c < Wson_i->numberOfDaughters(); ++ c){
                const reco::Candidate * TauSon = Wson_i->daughter(c);
                if(abs(TauSon->pdgId()) == 15){
		  //cout<<"Tau daughetrs "<<TauSon->numberOfDaughters()<<endl;
		  for(size_t d = 0; d < TauSon->numberOfDaughters(); ++ d){
		    const reco::Candidate * TauSon2 = TauSon->daughter(d);
		    int tausonid = abs(TauSon2->pdgId());
		    //cout<<"tau daughter Id "<<tausonid<<" status "<<TauSon2->status()<<endl;
		    if     (tausonid == 11){tempLepton = 11;}
		    else if(tausonid == 13){tempLepton = 13;}
		    //else if(tausonid == 12 || tausonid==14 || tausonid==16) neutrinos.push_back(TauSon2);
		  }
		}
	        else if(abs(TauSon->pdgId()) ==11 ) {tempLepton = 11;}
	        else if(abs(TauSon->pdgId()) ==13 ) {tempLepton = 13;}
	        //else if(abs(TauSon->pdgId())==12 || abs(TauSon->pdgId())==14 || abs(TauSon->pdgId())==16) neutrinos.push_back(TauSon);
	      }  
	      if     (tempLepton == 11) { chLeptonCounter++; electronCounter++;  }
	      else if(tempLepton == 13) { chLeptonCounter++; muonCounter++;      }
	      else                      { chLeptonCounter++; tauCounter++;       }	    
	    }
	    else{	  
	      switch(abs(id_Wson)){
	      case 1:  quarkCounter++;  break;
	      case 2:  quarkCounter++;  break;
	      case 3:  quarkCounter++;  break;
	      case 4:  quarkCounter++;  break;
	      case 5:  quarkCounter++;  break;
	      case 6:  quarkCounter++;  break;
	      case 11: chLeptonCounter++; electronCounter++; break;
	      case 13: chLeptonCounter++; muonCounter++;     break;
	      case 12: case 14: case 16:  break;
	      }
	    }
	  }
	}
      }
    
      int  wChannel = WUNKNOWN;
      if     (quarkCounter == 2)                          { wChannel = WQQ;    }      
      else if(quarkCounter == 0 && electronCounter == 1 ) { wChannel = WENU;   }
      else if(quarkCounter == 0 && muonCounter == 1     ) { wChannel = WMUNU;  }
      else if(quarkCounter == 0 && tauCounter == 1      ) { wChannel = WTAUNU; }
	
      //cout<<"WChannel "<<wChannel<<endl;

      return wChannel;

    }

    //
    int Event::assignTTEvent(const edm::Event& iEvent, const edm::EventSetup& iSetup,std::vector<edm::InputTag> *jpsources){
      //event info
      getEventInfo(iEvent,iSetup);

      //reset all
      int quarkCounter(0),chLeptonCounter(0),electronCounter(0),muonCounter(0),tauCounter(0);  
      tops.clear(); leptons.clear();  neutrinos.clear(); quarks.clear();         
      genVertex = TVector3(0,0,0);
      int nVerticesUsed(0);
	
      //retrieve the generator level particle collection      
      edm::Handle<reco::GenParticleCollection> genParticles;
      iEvent.getByLabel("genParticles", genParticles);
	
      //iterate over the collection and store t->Wb decays, also t->Hb decays
      std::vector<const reco::Candidate*> W_Sons;
      for(size_t i = 0; i < genParticles->size(); ++ i) {
	const reco::GenParticle & p = (*genParticles)[i];
	int id_p   = p.pdgId();   
	  
	if(p.status()==3) { genVertex += TVector3(p.vx(),p.vy(),p.vz()); nVerticesUsed++; }

	//select tops
	if(abs(id_p) != 6) continue;   
	if( p.status()==3) tops.push_back( &p );
	  
	for(size_t b = 0; b < p.numberOfDaughters(); ++ b){
	  const reco::Candidate * top_daughter = p.daughter(b);
	    
	  //store W and ch. higgs daughters
	  if(abs(top_daughter->pdgId()) == 24 || abs(top_daughter->pdgId()) == 37)
	    {                                 
	      for(size_t c = 0; c < top_daughter->numberOfDaughters(); ++c)
		{
		  const reco::Candidate * W_daughter = top_daughter->daughter(c);
		  if(abs(W_daughter->pdgId()) != 24 && abs(W_daughter->pdgId()) != 37) W_Sons.push_back(W_daughter);
		}
	    }
	  else if(abs(top_daughter->pdgId())<6 && abs(top_daughter->pdgId())!=0 
		  && abs(top_daughter->pdgId())!=22 ) {
	    quarks.push_back( top_daughter );
	  }
	}
      }



      //compute the mean of the vertices
      if(nVerticesUsed>0) genVertex *= 1./nVerticesUsed;
	
      //check W decay chain
      for(std::vector<const reco::Candidate*>::const_iterator Wson_i = W_Sons.begin(); Wson_i != W_Sons.end(); Wson_i++)
	{
	  int id_Wson = (*Wson_i)->pdgId();
	  
	  //taus must be traced further
	  if(abs((*Wson_i)->pdgId()) == 15)
	    {	    	         
	      int tempLepton = 0;
	      for(size_t c = 0; c < (*Wson_i)->numberOfDaughters(); ++ c){
		const reco::Candidate * TauSon = (*Wson_i)->daughter(c);
		if(abs(TauSon->pdgId()) == 15)
		  {
		    for(size_t d = 0; d < TauSon->numberOfDaughters(); ++ d){
		      const reco::Candidate * TauSon2 = TauSon->daughter(d);
		      int tausonid = abs(TauSon2->pdgId());
		      if     (tausonid == 11){tempLepton = 11; leptons.push_back ( TauSon2 ); }
		      else if(tausonid == 13){tempLepton = 13; leptons.push_back ( TauSon2 ); }
		      else if(tausonid == 12 || tausonid==14 || tausonid==16) neutrinos.push_back(TauSon2);
		    }
		  }
		else if(abs(TauSon->pdgId()) ==11 ) {tempLepton = 11; leptons.push_back ( TauSon ); }
		else if(abs(TauSon->pdgId()) ==13 ) {tempLepton = 13; leptons.push_back ( TauSon ); }
		else if(abs(TauSon->pdgId())==12 || abs(TauSon->pdgId())==14 || abs(TauSon->pdgId())==16) neutrinos.push_back(TauSon);
	      }
	      
	      if     (tempLepton == 11) { chLeptonCounter++; electronCounter++;  }
	      else if(tempLepton == 13) { chLeptonCounter++; muonCounter++;      }
	      else                      { chLeptonCounter++; tauCounter++;       leptons.push_back( *Wson_i );  }	    
	    }
	  else{	  
	    switch(abs(id_Wson)){
	    case 1:  quarkCounter++;  break;
	    case 2:  quarkCounter++;  break;
	    case 3:  quarkCounter++;  break;
	    case 4:  quarkCounter++;  break;
	    case 5:  quarkCounter++;  break;
	    case 6:  quarkCounter++;  break;
	    case 11: chLeptonCounter++; electronCounter++; leptons.push_back( *Wson_i); break;
	    case 13: chLeptonCounter++; muonCounter++;     leptons.push_back( *Wson_i); break;
	    case 12: case 14: case 16: neutrinos.push_back( *Wson_i ); break;
	    }
	  }
	}
	
      int ttChannel = UNKNOWN;
      if     (quarkCounter == 4) {ttChannel = ALLJETS;}
      else if(quarkCounter == 2 && electronCounter == 1) {ttChannel = EJETS;}
      else if(quarkCounter == 2 && muonCounter == 1) {ttChannel = MUJETS;}
      else if(quarkCounter == 2 && tauCounter == 1) {ttChannel = TAUJETS;}
      else if(quarkCounter == 0 && electronCounter == 2) {ttChannel = EE;}
      else if(quarkCounter == 0 && electronCounter == 1 && muonCounter == 1){ttChannel = EMU;}
      else if(quarkCounter == 0 && electronCounter == 1 && tauCounter  == 1){ttChannel = ETAU;}
      else if(quarkCounter == 0 && muonCounter == 2) {ttChannel = MUMU;}
      else if(quarkCounter == 0 && muonCounter == 1 && tauCounter == 1) {ttChannel = MUTAU;}
      else if(quarkCounter == 0 && tauCounter == 2) {ttChannel = TAUTAU;}
	
      tops.sort();      tops.unique();
      leptons.sort();   leptons.unique();
      quarks.sort();    quarks.unique();
      neutrinos.sort(); neutrinos.unique();
	
      //store also jet to partons correspondence
      fillJetToPartonMap(iEvent,iSetup,jpsources);
      cout<<endl;
      return ttChannel;
    }


    //
    void Event::fillPileupInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup)
    {
      genPUsummary_.clear();
      edm::Handle<PileupSummaryInfo> puInfoH;
      bool bPuInfo=iEvent.getByLabel("addPileupInfo", puInfoH);
      if (bPuInfo) 
	{
	  for(int i=0; i<puInfoH->getPU_NumInteractions(); i++)
	    {
	      std::vector<double> iVtxInfo(3,0);
	      iVtxInfo[0]=puInfoH->getPU_zpositions()[i];
	      iVtxInfo[1]=puInfoH->getPU_ntrks_lowpT()[i];
	      iVtxInfo[2]=puInfoH->getPU_ntrks_highpT()[i];
	      genPUsummary_.push_back(iVtxInfo);
	}
      }
    }

      
  }
}

