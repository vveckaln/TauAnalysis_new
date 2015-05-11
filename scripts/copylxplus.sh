#!/bin/bash
files="
MC8TeV_TTJetsMassiveBinDecay_muon_tau_TOTAL_out.root
Data8TeV_SingleMu2012_TOTAL_out.root 
MC8TeV_WJets_TOTAL_out.root
MC8TeV_single_t_TOTAL_out.root
MC8TeV_DYJetsToLL_TOTAL_out.root                               
MC8TeV_QCD_TOTAL_out.root                                       
MC8TeV_TTJetsMassiveBinDecay_other_ttbar_TOTAL_out.root
MC8TeV_diboson_TOTAL_out.root
"
for i in $files
do
    int=$((int + 1))
    if [ "$i" == "MC8TeV_TTJetsMassiveBinDecay_muon_tau_TOTAL_out.root" -o "$i" == "MC8TeV_WJets_TOTAL_out.root" ]
    then
	file=$file" /lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/hadd/"$i
    else
	file=$file" /lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/total_new/"$i
    fi

done 
scp -r $file vveckaln@lxplus.cern.ch:
