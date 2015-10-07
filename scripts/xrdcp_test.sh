#! bin/sh
export PROXYDIR=$FILES/RunII/FARM/inputs/x509_user_proxy
export X509_USER_PROXY=$PROXYDIR/x509_proxy;
export XrdSecDEBUG=2
#file=root://cms-xrd-global.cern.ch//store/mc/RunIISpring15DR74/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt#50ns_MCRUN2_74_V9A-v1/70000/3AF88FC5-A513-E511-B801-00259073E514.root
#file=root://cms-xrd-global.cern.ch//store/mc/Phys14DR/DYJetsToLL_M-50_13TeV-madgraph-pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/\
#  00000/A266FB5C-796C-E411-B6EE-0025901D493E.root
file=root://cms-xrd-global.cern.ch//store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/10000/A89CCB89-4106-E511-BB7C-00259073E4A0.root
dataset=WW
for ind in {0..100}
do
   output_file=xrdcp_test$ind.txt
   
   echo -e "xrdcp -f -d 1 "$file" /dev/null\n" > $output_file
   echo -e `date`" dataset: "$dataset"\n\n" >> $output_file; 
   xrdcp -f -d 1 $file /dev/null >> $output_file 2>&1; cat $output_file
done