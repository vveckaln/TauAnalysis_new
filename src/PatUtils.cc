#include "LIP/TauAnalysis/interface/PatUtils.h"

namespace patUtils
{
  /*  bool passId(pat::Electron * el,  reco::Vertex * vtx, const unsigned char IdLevel)
  {
    
    //for electron Id look here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2
    //for the meaning of the different cuts here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaCutBasedIdentification
    const float sigmaletaleta  = el -> sigmaIetaIeta();
    const float dEtaln         = fabs(el -> deltaEtaSuperClusterTrackAtVtx());
    const float dPhiln         = fabs(el -> deltaPhiSuperClusterTrackAtVtx());
    const float hem            = el -> hadronicOverEm();
    const double resol         = fabs(1/el -> ecalEnergy() - 1/el -> trackMomentumAtVtx().p());
    const double dxy           = fabs(el -> gsfTrack() -> dxy(vtx -> position()));
    const double dz            = fabs(el -> gsfTrack() -> dz(vtx -> position())); 
    const double mHits         = el -> gsfTrack() -> trackerExpectedHitsInner().numberOfHits();//hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
    
    const bool barrel = (fabs(el -> superCluster() -> eta()) <= 1.479);
    const bool endcap = (!barrel && fabs(el -> superCluster() -> eta()) < 2.5);
    const unsigned char region = 0;
    if (endcap) 
      region = 1;
    //Veto Loose Medium Tight
    static const float full5x5_sigmaIetaIeta_ref[2][2][4] = 
      {
	{
	  {0.012,  0.0105, 0.0101, 0.0101},
	  {0.0339, 0.0318, 0.0287, 0.0287}
	},
	{
	  {0.0114, 0.0103, 0.0101, 0.0101},
	  {0.0352, 0.0301, 0.0283, 0.0279}
	}
      };

    static const float abs_dEtaIn_ref[2][2][4] =
      {
	{
	  {0.0126, 0.00976, 0.0094, 0.00864},
	  {0.0109, 0.00952, 0.00773, 0.00762}
	},
	{
	  {0.0152, 0.0105, 0.0103, 0.00926 },
	  {0.0113, 0.00814, 0.00733, 0.00724}
	}
      };
    static const float abs_dPhiIn_ref[2][2][4] =
      {
	{
	  {0.107, 0.0929, 0.0296, 0.0286},
	  {0.219, 0.181, 0.148, 0.0439 }
	},
	{
	  {0.216, 0.115, 0.0336, 0.0336 },
	  {0.237, 0.182, 0.114, 0.0918}
	}
      };
	
    static const float hOverE_ref[2][2][4] =
      {
	{
	  {0.186, 0.0765, 0.0372, 0.0342 },
	  {0.0962, 0.0824, 0.0546, 0.0544}
	},
	{
	  {0.181, 0.104, 0.0876, 0.0597  },
	  {0.116, 0.0897, 0.0678, 0.0615 }
	}
      };
    static const float relIsoWithEA_ref[2][2][4] =
      {
	{
	  {0.161, 0.118, 0.0987, 0.0591 },
	  {0.193, 0.118, 0.0902, 0.0759  }
	},
	{
	  {0.126, 0.0893, 0.0766, 0.0354  },
	  {0.144, 0.121, 0.0678, 0.0646  }
	}
      };
  
    static const float ooEmooP_ref[2][2][4] =
      {
	{
	  {0.239, 0.184, 0.118, 0.0116 },
	  {0.141, 0.125, 0.104, 0.01  }
	},
	{
	  {0.207, 0.102, 0.0174, 0.012  },
	  {0.174, 0.126, 0.0898, 0.00999  }
	}
      };
  
    static const float abs_d0_ref[][2][4] =
      {
	{
	  {0.0621, 0.0227, 0.0151, 0.0103 },
	  {0.279, 0.242, 0.0535, 0.0377  }
	},
	{
	  {0.279, 0.242, 0.0535, 0.0377  },
	  {0.222, 0.118, 0.0739, 0.0351 }
	}
      };

    static const float abs_dz_ref[2][2][4] =
      {
	{
	  {0.613, 0.379, 0.238, 0.170 },
	  {0.947, 0.921, 0.572, 0.571 }
	},
	{
	  {0.472, 0.41, 0.373, 0.0466  },
	  {0.921, 0.822, 0.602, 0.417 }
	}
      };

    static const unsigned char expectedMissingInngerHits[2][2][4] =
      {
	{
	  {2, 2, 2, 2  },
	  {3, 1, 1, 1  }
	},
	{
	  {2, 2, 2, 2  },
	  {3, 1, 1, 1 }
	}
      };

    static const unsigned char expectedMissingInngerHits[2][2][4] =
      {
	{
	  {2, 2, 2, 2  },
	  {3, 1, 1, 1  }
	},
	{
	  {2, 2, 2, 2  },
	  {3, 1, 1, 1 }
	}
      };

    static const bool pass_conv_veto_ref[2][2][4] = 
      {
	{
	  {true, true, true, true},
	  {true, true, true, true}
	},
	{
	  {true, true, true, true},
	  {true, true, true, true}
	}
      };
  

    if (
	sigmaletaleta < full5x5_sigmaIetaIeta_ref[grun][region][IdLevel] and
	dEtaln < abs_dEtaIn_ref[grun][region][IdLevel] and
	dPhiln < abs_dPhiIn_ref[grun][region][IdLevel] and
	hem < hOverE_ref[grun][region][IdLevel] and 
	resol < relIsoWithEA_ref[grun][region][IdLevel] and
	dxy < abs_d0_ref[grun][region][IdLevel] and
	dz < abs_dz_ref[grun][region][IdLevel] and
	mHits < expectedMissingInngerHits[grun][region][IdLevel])
	return true;
	return false;
    // PHYS14 selection 
    switch(IdLevel){
    case llvvElecId::Veto :
      if(barrel                   &&
         dEtaln        < 0.013625 &&
         dPhiln        < 0.230374 &&
         sigmaletaleta < 0.011586 &&
         hem           < 0.181130 &&
         dxy           < 0.094095 &&
         dz            < 0.713070 &&
         resol         < 0.295751 &&
         mHits         <=2          )
        return true;
      if(endcap                   &&
         dEtaln        < 0.011932 &&
         dPhiln        < 0.255450 &&
         sigmaletaleta < 0.031849 &&
	 hem           < 0.223870 &&
         dxy           < 0.342293 &&
         dz            < 0.953461 &&
         resol         < 0.155501 &&
         mHits <= 3                )
        return true;
      break;
      
    case llvvElecId::Loose :
      if(barrel                   &&
         dEtaln        < 0.009277 &&
         dPhiln        < 0.094739 &&
         sigmaletaleta < 0.010331 &&
         hem           < 0.093068 &&
         dxy           < 0.035904 &&
         dz            < 0.075496 &&
         resol         < 0.189968 &&
         mHits         <= 1        )
        return true; 
      if(endcap                   &&
         dEtaln        < 0.009833 &&
         dPhiln        < 0.149934 &&
         sigmaletaleta < 0.031838 &&
         hem           < 0.115754 &&
         dxy           < 0.099266 &&
         dz            < 0.197897 &&
         resol         < 0.140662 &&
         mHits         <= 1      )
	return true; 
      break;
      
    case llvvElecId::Medium :
      if(barrel                     &&
         dEtaln          < 0.008925 &&
         dPhiln          < 0.035973 &&
         sigmaletaleta   < 0.009996 &&
         hem             < 0.050537 &&
         dxy             < 0.012235 &&
         dz              < 0.042020 &&
         resol           < 0.091942 &&
         mHits           <= 1      )
        return true; 
      if(endcap                     &&
         dEtaln          < 0.007429 &&
         dPhiln          < 0.067879 &&
         sigmaletaleta   < 0.030135 &&
         hem             < 0.086782 &&
         dxy             < 0.036719 &&
         dz              < 0.138142 &&
         resol           < 0.100683 &&
         mHits            <= 1)
        return true; 
      break;
  
    case llvvElecId::Tight :
      if(barrel                   &&
         dEtaln          < 0.006046 &&
         dPhiln          < 0.028092 &&
         sigmaletaleta   < 0.009947 &&
         hem             < 0.045772 &&
         dxy             < 0.008790 &&
         dz              < 0.021226 &&
         resol           < 0.020118 &&
         mHits           <= 1      )
        return true; 
      if(endcap                   &&
         dEtaln          < 0.007057 &&
         dPhiln          < 0.030159 &&
         sigmaletaleta   < 0.028237 &&
         hem             < 0.067778 &&
         dxy             < 0.027984 &&
         dz              < 0.133431 &&
         resol           < 0.098919 &&
         mHits           <= 1      )
	return true; 
      break;
      
    case llvvElecId::LooseMVA :
    case llvvElecId::MediumMVA :
    case llvvElecId::TightMVA :
      printf("FIXME: MVA ID not yet implemented for the electron\n");
      return false;
      break;
                  
    default:
      printf("FIXME ElectronId llvvElecId::%i is unkown\n", IdLevel);
      return false;
      break;
    }
    return false;
    }*/
  
  bool passId(pat::Muon& mu,  reco::Vertex& vtx, int IdLevel){
    //for muon Id look here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#LooseMuon

    // Muon IDs for 74X are supposed to be already implemented in the standard pat::Muon methods (see https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2015#Muons )
    // They are added here as "StdLoose", "StdTight" etc
    switch(IdLevel){
      
    case llvvMuonId::Loose :
      if(mu.isPFMuon() && (mu.isGlobalMuon() || mu.isTrackerMuon()))return true;
      break;
      
    case llvvMuonId::Soft :
      if(mu.isPFMuon() && mu.isTrackerMuon() && mu.muonID("TMOneStationTight") && mu.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 && mu.innerTrack()->hitPattern().pixelLayersWithMeasurement() > 1 &&
         fabs(mu.innerTrack()->dxy(vtx.position())) < 0.3 && fabs(mu.innerTrack()->dz(vtx.position())) < 20. && mu.innerTrack()->normalizedChi2() < 1.8) return true;
      break;
      
    case llvvMuonId::Tight :
      if( mu.isPFMuon() && mu.isGlobalMuon() && mu.globalTrack()->normalizedChi2() < 10. && mu.globalTrack()->hitPattern().numberOfValidMuonHits() > 0. && mu.numberOfMatchedStations() > 1 &&
          fabs(mu.muonBestTrack()->dxy(vtx.position())) < 0.2 && fabs(mu.muonBestTrack()->dz(vtx.position())) < 0.5 && mu.innerTrack()->hitPattern().numberOfValidPixelHits() > 0 &&
          mu.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5)return true;
      break;
      
    case llvvMuonId::StdLoose :
      if(mu.isLooseMuon()) return true;
      break;
      
    case llvvMuonId::StdSoft :
      if(mu.isSoftMuon(vtx)) return true;
      break;
      
    case llvvMuonId::StdTight :
      if(mu.isTightMuon(vtx)) return true;
      break;
      
    default:
      printf("FIXME MuonId llvvMuonId::%i is unkown\n", IdLevel);
      return false;
      break;
    }
    return false;
  }  
  
  bool passId(pat::Photon& photon, double rho, int IdLevel){
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2
    // CSA14 selection, conditions: 25ns, better detector alignment. 
    // Used Savvas Kyriacou's slides, mailed from Ilya. 
    
    bool elevto = photon.hasPixelSeed();
    
    // sigma ieta ieta
    // full5x5 is not ready in 720 yet 
    // float sigmaIetaIeta = photon.full5x5_sigmaIetaIeta();
    // taken from https://github.com/cms-sw/cmssw/blob/CMSSW_7_2_X/PhysicsTools/PatAlgos/plugins/PATPhotonSlimmer.cc#L119-L130
    
    // float sigmaIetaIeta = photon.sigmaIetaIeta(); 
    float sigmaIetaIeta = photon.userFloat("sigmaIetaIeta_NoZS"); 

    // H/E 
    float hoe = photon.hadTowOverEm();

    // isolation
    double pt=photon.pt();
    double eta=photon.superCluster()->eta();

    float chIso = photon.chargedHadronIso(); 
    float chArea = utils::cmssw::getEffectiveArea(22,eta,3,"chIso"); 

    float nhIso = photon.neutralHadronIso();
    float nhArea = utils::cmssw::getEffectiveArea(22,eta,3,"nhIso");

    float gIso = photon.photonIso();
    float gArea = utils::cmssw::getEffectiveArea(22,eta,3,"gIso");

    bool barrel = (fabs(eta) <= 1.479);
    bool endcap = (!barrel && fabs(eta) < 2.5);

    // PHYS14 selections PU20 bunch crossing 25 ns
    switch(IdLevel){
    case llvvPhotonId::Loose :
        
      if ( barrel
	   && !elevto
	   && hoe < 0.028
	   && sigmaIetaIeta < 0.0107
	   && TMath::Max(chIso-chArea*rho,0.0) < 2.67 
	   && TMath::Max(nhIso-nhArea*rho,0.0) < 7.23 + exp(0.0028*pt + 0.5408) 
	   && TMath::Max(gIso-gArea*rho,  0.0) < 2.11 + 0.0014*pt )
	return true; 
      if ( endcap
	   && !elevto
	   && hoe < 0.093
	   && sigmaIetaIeta < 0.0272
	   && TMath::Max(chIso-chArea*rho,0.0) < 1.79
	   && TMath::Max(nhIso-nhArea*rho,0.0) < 8.89 + 0.01725*pt
	   && TMath::Max(gIso-gArea*rho,  0.0) < 3.09 + 0.0091*pt )
	return true; 
            
      break;
      
    case llvvPhotonId::Medium :

      if ( barrel
	   && !elevto
	   && hoe < 0.012
	   && sigmaIetaIeta < 0.0100
	   && TMath::Max(chIso-chArea*rho,0.0) < 1.79 
	   && TMath::Max(nhIso-nhArea*rho,0.0) < 0.16 + exp(0.0028*pt+0.5408) 
	   && TMath::Max(gIso-gArea*rho,  0.0) < 1.90 + 0.0014*pt )
	return true; 
      if ( endcap
	   && !elevto
	   && hoe < 0.023
	   && sigmaIetaIeta < 0.0267
	   && TMath::Max(chIso-chArea*rho,0.0) < 1.09 
	   && TMath::Max(nhIso-nhArea*rho,0.0) < 4.31 + 0.0172*pt
	   && TMath::Max(gIso-gArea*rho,  0.0) < 1.90 + 0.0091*pt )
	return true; 
            
      break;
    case llvvPhotonId::Tight :

      if ( barrel
	   && !elevto
	   && hoe < 0.010
	   && sigmaIetaIeta < 0.0100
	   && TMath::Max(chIso-chArea*rho,0.0) < 1.66 
	   && TMath::Max(nhIso-nhArea*rho,0.0) < 0.14 + exp(0.0028*pt+0.5408) 
	   && TMath::Max(gIso-gArea*rho,  0.0) < 1.40 + 0.0014*pt )
	return true; 
      if ( endcap
	   && !elevto
	   && hoe < 0.015
	   && sigmaIetaIeta < 0.0265
	   && TMath::Max(chIso-chArea*rho,0.0) < 1.04 
	   && TMath::Max(nhIso-nhArea*rho,0.0) < 3.89 + 0.0172*pt
	   && TMath::Max(gIso-gArea*rho,  0.0) < 1.40 + 0.0091*pt )
	return true; 
            
      break;
      
    default:
      printf("FIXME PhotonId llvvPhotonId::%i is unkown\n", IdLevel);
      return false;
      break;
      
    }    
    
    return false; 
  }
  
  bool passIso(pat::Electron& el, int IsoLevel, double rho){
          //https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2
          float  chIso   = el.pfIsolationVariables().sumChargedHadronPt;
          float  nhIso   = el.pfIsolationVariables().sumNeutralHadronEt;
          float  gIso    = el.pfIsolationVariables().sumPhotonEt;

	  float  relIso = 0.0; 
	  
	  if (rho == 0) {
	    float  puchIso = el.pfIsolationVariables().sumPUPt; 
	    relIso  = (chIso + TMath::Max(0.,nhIso+gIso-0.5*puchIso)) / el.pt();
	  }
	  else {
	    float effArea = utils::cmssw::getEffectiveArea(11,el.superCluster()->eta(),3);
	    relIso  = (chIso + TMath::Max(0.,nhIso+gIso-rho*effArea)) / el.pt();
	  }
	  
          bool barrel = (fabs(el.superCluster()->eta()) <= 1.479);
          bool endcap = (!barrel && fabs(el.superCluster()->eta()) < 2.5);

	  // PHYS14 selection, conditions: PU20 bx25
          switch(IsoLevel){
               case llvvElecIso::Veto :
                  if( barrel && relIso < 0.158721 ) return true;
                  if( endcap && relIso < 0.177032 ) return true;
                  break;

               case llvvElecIso::Loose :
                  if( barrel && relIso < 0.130136 ) return true;
                  if( endcap && relIso < 0.163368 ) return true;
                  break;

               case llvvElecIso::Medium :
                  if( barrel && relIso < 0.107587 ) return true;
                  if( endcap && relIso < 0.113254 ) return true;
                  break;

               case llvvElecIso::Tight :
                  if( barrel && relIso < 0.069537 ) return true;
                  if( endcap && relIso < 0.078265 ) return true;
                  break;

               default:
                  printf("FIXME MuonIso llvvMuonIso::%i is unkown\n", IsoLevel);
                  return false;
                  break;
          }
          return false;  
   }

   bool passIso(pat::Muon& mu, int IsoLevel){
          //https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Muon_Isolation
          float  chIso   = mu.pfIsolationR04().sumChargedHadronPt;
          float  nhIso   = mu.pfIsolationR04().sumNeutralHadronEt;
          float  gIso    = mu.pfIsolationR04().sumPhotonEt;
          float  puchIso = mu.pfIsolationR04().sumPUPt;
          float  relIso  = (chIso + TMath::Max(0.,nhIso+gIso-0.5*puchIso)) / mu.pt();

          switch(IsoLevel){
               case llvvMuonIso::Loose : 
                  if( relIso < 0.20 ) return true;
                  break;

               case llvvMuonIso::Tight :
                  if( relIso < 0.12 ) return true;
                  break;

               default:
                  printf("FIXME MuonIso llvvMuonIso::%i is unkown\n", IsoLevel);
                  return false;
                  break;
          }
          return false;          
   }

  bool passPhotonTrigger(fwlite::ChainEvent ev, float &triggerThreshold,
			 float &triggerPrescale ){
    edm::TriggerResultsByName tr = ev.triggerResultsByName("HLT");
    if( !tr.isValid() ) return false;

    bool hasPhotonTrigger(false);
    // float triggerPrescale(1.0); 
    // float triggerThreshold(0);
    triggerPrescale = 1.0; 
    triggerThreshold = 0.0;

    std::string successfulPath="";
    if( utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon300_*")){
      hasPhotonTrigger=true;
      triggerThreshold=300;
    }
    else if( utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon250_*")){
      hasPhotonTrigger=true;
      triggerThreshold=250;
    }
    // else if( utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon160_*")){
    //   hasPhotonTrigger=true;
    //   triggerThreshold=160;
    // }
    // else if( utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon150_*")){
    //   hasPhotonTrigger=true;
    //   triggerThreshold=150;
    // }
    // else if( utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon135_*")){
    //   hasPhotonTrigger=true;
    //   triggerThreshold=135;
    // }
    else if( utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_*")){
      hasPhotonTrigger=true;
      triggerThreshold=120;
    }
    else if( utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_*")){
      hasPhotonTrigger=true;
      triggerThreshold=90;
    }
    else if(utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_*")){
      hasPhotonTrigger=true;
      triggerThreshold=75;
    }
    else if(utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_*")){
      hasPhotonTrigger=true;
      triggerThreshold=50;
    }
    else if(utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_*")){
      hasPhotonTrigger=true;
      triggerThreshold=36;
    }
    else if(utils::passTriggerPatternsAndGetName(tr, successfulPath, "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_*")){
      hasPhotonTrigger=true;
      triggerThreshold=22;
    }
      
    if(successfulPath!=""){ //get the prescale associated to it
      fwlite::Handle< pat::PackedTriggerPrescales > prescalesHandle;
      prescalesHandle.getByLabel(ev, "patTrigger");
      pat::PackedTriggerPrescales prescales = *prescalesHandle;
      const edm::TriggerResults& trResults =  prescales.triggerResults();
      prescales.setTriggerNames( ev.triggerNames(trResults) );
      triggerPrescale = prescales.getPrescaleForName(successfulPath);
    }

    return hasPhotonTrigger; 
  }


  bool passPFJetID(std::string label,
                  pat::Jet jet){

    bool passID = false;

    float rawJetEn(jet.correctedJet("Uncorrected").energy() );
    // Note: All fractions are calculated with the raw/uncorrected energy of the jet (only then they add up to unity). So the PF JetID has to be applied before the jet energy corrections. 

    float nhf( (jet.neutralHadronEnergy() + jet.HFHadronEnergy())/rawJetEn );
    float nef( jet.neutralEmEnergy()/rawJetEn );
    float cef( jet.chargedEmEnergy()/rawJetEn );
    float chf( jet.chargedHadronEnergy()/rawJetEn );
    float nch    = jet.chargedMultiplicity();
    float nconst = jet.numberOfDaughters();
    float muf( jet.muonEnergy()/rawJetEn);

    //From https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_data
    if (label == "Loose") passID = ( (nhf<0.99  && nef<0.99 && nconst>1 && muf < 0.8 ) && ( fabs(jet.eta())>2.4||(fabs(jet.eta()) <= 2.4 && chf>0 && nch>0 && cef<0.99) ) );
    if (label == "Tight") passID = ( (nhf<0.90  && nef<0.90 && nconst>1 && muf < 0.8 ) && ( fabs(jet.eta())>2.4||(fabs(jet.eta()) <= 2.4 && chf>0 && nch>0 && cef<0.90) ) );

    return passID;
  }

  bool passPUJetID(pat::Jet j){

    double jpt = j.pt();
    double jeta = j.eta();

    //Recommendation of HZZ :https://twiki.cern.ch/twiki/bin/view/CMS/HiggsZZ4l2015#Jets
    float jpumva=0.;
    jpumva=j.userFloat("pileupJetId:fullDiscriminant");

    bool passPU = true;
    if(jpt>20){
      if(jeta>3.){
        if(jpumva<=-0.45)passPU=false;
      }else if(jeta>2.75){
        if(jpumva<=-0.55)passPU=false;
      }else if(jeta>2.5){
        if(jpumva<=-0.6)passPU=false;
      }else if(jpumva<=-0.63)passPU=false;
    }else{ //pt<20 : in the 2l2nu analysis, this means 15<pt<20
      if(jeta>3.){
        if(jpumva<=-0.95)passPU=false;
      }else if(jeta>2.75){
        if(jpumva<=-0.94)passPU=false;
      }else if(jeta>2.5){
        if(jpumva<=-0.96)passPU=false;
      }else if(jpumva<=-0.95)passPU=false;
    }
    return passPU;
  }




}
