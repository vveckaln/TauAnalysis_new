import FWCore.ParameterSet.Config as cms

PhysicsAnalysisParSet = cms.PSet(
    input = cms.vstring('/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/output_hadd/Data8TeV_SingleMu2012A_TOTAL_out.root', 
                        '/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/output_hadd/Data8TeV_SingleMu2012B_TOTAL_out.root', 
                        '/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/output_hadd/Data8TeV_SingleMu2012C_TOTAL_out.root', 
                        '/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/output_hadd/Data8TeV_SingleMu2012D_TOTAL_out.root'),
    outdir = cms.string("/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output"),
    isData = cms.bool(True),
    XSection = cms.double(1.0),
    debug = cms.bool(False),
    mctruthmode = cms.int32(0)
)
