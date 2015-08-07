DIR=/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_7_4_2/src/LIP/TauAnalysis/src

for file in $DIR/*;
do
    sed -i "s/CPHistogramPoolRegister/Register/;s/cpHistogramPoolRegister/cpregister/;/cpFileRegister/d;/CPFileRegister/d;/CPFilePoolRegister/d" $file
# > $DIR/tempfile.tmp
#    mv $DIR/tempfile.tmp $file
done