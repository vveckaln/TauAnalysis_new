#! /bin/sh

output_file=$FILES/RunII/output/event_analysis/Data13TeV_SingleMuon2015BPromptReco/luminosities/total.json
if [ -f $output_file ]; then
    rm $output_file
fi
for file in $FILES/RunII/output/event_analysis/Data13TeV_SingleMuon2015BPromptReco/luminosities/*.json
do
    if [ "$file" == "$output_file" ]; then
	continue
    fi
    cat $file >> $output_file
done


sed -ie "s#}{#, #g" $output_file 
sed -ie "s#, ,#, #g" $output_file
