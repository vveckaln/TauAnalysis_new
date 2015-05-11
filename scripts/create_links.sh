files="MC8TeV_QCD_TOTAL_out.root
MC8TeV_TTJetsMassiveBinDecay_dilepton_muon_electron_TOTAL_out.root
MC8TeV_TTJetsMassiveBinDecay_dilepton_muon_muon_TOTAL_out.root
MC8TeV_TTJetsMassiveBinDecay_hadronic_TOTAL_out.root
MC8TeV_TTJetsMassiveBinDecay_lepton_jets_TOTAL_out.root
MC8TeV_TTJetsMassiveBinDecay_muon_tau_TOTAL_out.root
MC8TeV_TTJetsMassiveBinDecay_tau_jets_TOTAL_out.root
MC8TeV_TTJetsMassiveBinDecay_tau_tau_TOTAL_out.root
MC8TeV_WJets_TOTAL_out.root
MC8TeV_diboson_TOTAL_out.root
MC8TeV_single_t_TOTAL_out.root
MC8TeV_DYJetsToLL_TOTAL_out.root
"

folder=("total_new"
"hadd"
"hadd"
"hadd"
"hadd"
"hadd"
"hadd"
"hadd"
"hadd"
"total_new"
"total_new"
"total_new"
)
int=0
INPUT=/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/
OUTPUT=/lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output/output_files/tau_fakes_input/
for i in $files
do
    #echo ${folder[$int]}

    #echo $int  $INPUT${folder[int]}/$i $OUTPUT$i 
    ln -s $INPUT${folder[int]}/$i $OUTPUT$i 
            int=$((int + 1))

done

