#! /bin/sh

output_file=$FILES/RunII/output/event_analysis/Data13TeV_SingleMuon2015BPromptReco/luminosities/total.json
rm $output_file
for file in $FILES/RunII/output/event_analysis/Data13TeV_SingleMuon2015BPromptReco/luminosities/*.json
do
    if [ "$file" == "$output_file" ]; then
	continue
    fi
    cat $file >> $output_file
done


sed -ie "s#}{#, #g" $output_file 
sed -ie "s#, ,#, #g" $output_file
