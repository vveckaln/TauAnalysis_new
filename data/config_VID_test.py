

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

PhysicsAnalysisParSet = cms.PSet(
    dtag           = cms.string("@dtag"),
    dset           = cms.string("@dset"),
    site           = cms.string("@site"),
    input          = cms.untracked.vstring("@input"),
    outdir         = cms.string("@outdir"),
    work_directory = cms.string("@work_directory"),
    isData         = cms.bool(@isData),
    XSection       = cms.double(@xsec),
    debug          = cms.bool(@debug),
    mctruthmode    = cms.int32(@mctruthmode),
    file_split     = cms.int32(@file_split),
    segment        = cms.int32(@segment),
    lumisToProcess = LumiList.LumiList(filename = @lumiMask).getVLuminosityBlockRange(),
)
