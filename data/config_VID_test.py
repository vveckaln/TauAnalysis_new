

import FWCore.ParameterSet.Config as cms
process = cms.Process("AnalysisProc")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
import PhysicsTools.PythonAnalysis.LumiList as LumiList
LumiList.LumiList().getVLuminosityBlockRange()
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('') )
from RecoJets.JetProducers.PileupJetIDParams_cfi import cutbased as pu_jetid
#from UserCode.llvv_fwk.mvaConfig_cfi import ewkzp2jFullNoQG as mySignalMVA
from CERN_RTU.TauAnalysis.mvaConfig_cfi import ewkzp2jFull as mySignalMVA
#from UserCode.llvv_fwk.mvaConfig_cfi import ewkzp2jBase as mySignalMVA

#
# Set up electron ID (VID framework)
#
useAOD = False
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
# turn on VID producer, indicate data format  to be
# DataFormat.AOD or DataFormat.MiniAOD, as appropriate 
if useAOD == True :
    dataFormat = DataFormat.AOD
else :
    dataFormat = DataFormat.MiniAOD

switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_50ns_V2_cff',
                 'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']

#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.ntupler = cms.EDAnalyzer(
    'ElectronNtuplerVIDDemo',
    # The module automatically detects AOD vs miniAOD, so we configure both
    #
    # Common to all formats objects
    #
    beamSpot = cms.InputTag('offlineBeamSpot'),
    #
    # Objects specific to AOD format
    #
    electrons    = cms.InputTag("gedGsfElectrons"),
    genParticles = cms.InputTag("genParticles"),
    vertices     = cms.InputTag("offlinePrimaryVertices"),
    conversions  = cms.InputTag('allConversions'),
    #
    # Objects specific to MiniAOD format
    #
    electronsMiniAOD    = cms.InputTag("slimmedElectrons"),
    genParticlesMiniAOD = cms.InputTag("prunedGenParticles"),
    verticesMiniAOD     = cms.InputTag("offlineSlimmedPrimaryVertices"),
    conversionsMiniAOD  = cms.InputTag('reducedEgamma:reducedConversions'),
    #
    # ID decisions (common to all formats)
    #
    eleVetoIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-veto"),
    eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-loose"),
    eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-medium"),
    eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-tight"),
    eleHEEPIdMap = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60"),
    # An example of configuration for accessing the full cut flow info for
    # one case is shown below.
    # The map name for the full info is the same as the map name of the
    # corresponding simple pass/fail map above, they are distinguished by
    # the type of the content.
    eleMediumIdFullInfoMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-medium"),
    # This is a fairly verbose mode if switched on, with full cut flow 
    # diagnostics for each candidate. Use it in a low event count test job.
    eleIdVerbose = cms.bool(False)
    )
outputFile = "VID_test_output.root"
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string( outputFile )
                                   )

# Make sure to add the ID sequence upstream from the user analysis module
process.p = cms.Path(process.egmGsfElectronIDSequence * process.ntupler)

PhysicsAnalysisParSet = cms.PSet(
    dtag           = cms.string("@dtag"),
    dset           = cms.string("@dset"),
    site           = cms.string("@site"),
    input          = cms.untracked.vstring("@input"),
    outdir         = cms.string("@outdir"),
    work_directory = cms.string("@work_directory")
)
