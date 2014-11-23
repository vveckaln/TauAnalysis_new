import FWCore.ParameterSet.Config as cms

PhysicsAnalysisParSet = cms.PSet(
    input_file_name       = cms.string("/lustre/ncg.ingrid.pt/cmst3/store/user/cbeiraod/14_08_06_2l2nu_EDMtuples_merged/MC8TeV_TTJetsFullLeptMGDecays_0.root"),
    noUncertainties     = cms.bool(True),
    eChONmuChOFF        = cms.bool(False),
    spyObjectSpecifiers = cms.string("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_11/src/LIP/TopTaus/histogram_specifiers/spec_output_histograms.xml"),
    spyMCDataSampleSpecifiers = cms.string("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_11/src/LIP/TopTaus/histogram_specifiers/spec_MCsamples.xml"),
    spyDataSampleSpecifiers = cms.string("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_11/src/LIP/TopTaus/histogram_specifiers/spec_datasamples.xml"),
    spyInputArea        = cms.string("/lustre/ncg.ingrid.pt/cmslocal/samples/tauDileptonSpyFiles_2014-06-25_CMSSW_5_3_9/spyInput/"), 

    spyOutputArea       = cms.string("/lustre/ncg.ingrid.pt/cmslocal/viesturs/spy_analysis_output/"),
    PileUpFileName      = cms.string("/exper-sw/cmst3/cmssw/users/vischia/chiggs/CMSSW_5_3_9/src/LIP/TopTaus/data/pileup/MyDataPileupHistogram_70300_100bins.root"),
    ptResolFileName     = cms.string("${CMSSW_RELEASE_BASE}/src/CondFormats/JetMETObjects/data/Spring10_PtResolution_AK5PF.txt"),
    etaResolFileName    = cms.string("${CMSSW_RELEASE_BASE}/src/CondFormats/JetMETObjects/data/Spring10_EtaResolution_AK5PF.txt"),
    phiResolFileName    = cms.string("${CMSSW_RELEASE_BASE}/src/CondFormats/JetMETObjects/data/Spring10_PhiResolution_AK5PF.txt"),
    jesUncFileName      = cms.string("/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_5_3_11/src/LIP/TopTaus/data/Summer13_V4_DATA_UncertaintySources_AK5PFchs.txt")
   
 )

