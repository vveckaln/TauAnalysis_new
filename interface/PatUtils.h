#ifndef patutils_h
#define patutils_h


#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/Common/interface/MergeableCounter.h"

//Load here all the dataformat that we will need
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"

//need for the good lumi filter
#include "DataFormats/Provenance/interface/LuminosityBlockID.h"
#include "DataFormats/Provenance/interface/LuminosityBlockRange.h"
#include "FWCore/Utilities/interface/Algorithms.h"

#include "CondFormats/JetMETObjects/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "LIP/TauAnalysis/interface/MacroUtils.h"
#include "LIP/TauAnalysis/interface/LumiUtils.h"

#include <vector>
#include "TVector3.h"
#include "TMath.h"
#include "TGraph.h"
#include <Math/VectorUtil.h>

namespace patUtils
{
   typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

   //define a generic container to hold information related to pat electrons, muons, taus
   //very weirdly, it seems it's the best way to do it...
   class GenericLepton  : public pat::GenericParticle {
      public:
      // constructor
      ~GenericLepton(){};
       GenericLepton(pat::Electron el_) : pat::GenericParticle(el_){el = el_; };
       GenericLepton(pat::Muon     mu_) : pat::GenericParticle(mu_){mu = mu_; };
         pat::Electron el;
         pat::Muon     mu;
   };

   namespace llvvElecId { enum ElecId  {Veto, Loose, Medium, Tight, LooseMVA, MediumMVA, TightMVA}; }
   namespace llvvMuonId { enum MuonId  {Loose, Soft, Tight, StdLoose, StdSoft, StdTight}; }
   namespace llvvPhotonId { enum PhotonId  {Loose, Medium, Tight}; }
   namespace llvvElecIso{ enum ElecIso {Veto, Loose, Medium, Tight}; }
   namespace llvvMuonIso{ enum MuonIso {Loose,Tight}; }

   bool passId (pat::Electron* el,  reco::Vertex* vtx, const unsigned char IdLevel);
   bool passId (pat::Muon&     mu,  reco::Vertex& vtx, int IdLevel);
   bool passId (pat::Photon& photon,  double rho, int IdLevel);
   bool passIso(pat::Electron& el,  int IsoLevel, double rho=0.0);
   bool passIso(pat::Muon&     mu,  int IsoLevel);
   bool passPhotonTrigger(fwlite::ChainEvent ev, float &triggerThreshold, float &triggerPrescale); 
   bool passPFJetID(std::string label, pat::Jet jet);
   bool passPUJetID(pat::Jet j);
}

#endif
