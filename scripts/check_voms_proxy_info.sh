#! /bin/sh
for file in /afs/cern.ch/work/v/vveckaln/private/RunII/FARM/outputs/proxy_test/*
do
    result=""
    while read line
    do
	result+=$line 
    done < $file
    if [ "$result" == "" ] 
    then
	echo "empty "$file
    fi
done