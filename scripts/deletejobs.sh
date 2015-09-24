#!/bin/bash


user=`whoami`

if [ `hostname | cut -d "." -f2-4` == "ncg.ingrid.pt" ] ; then  
    var=$( qstat -u $user | grep -oE "[[:digit:]]{7}")
    for i in ${var[@]} 
    do
	echo $i
	qdel $i
    done
elif [ `hostname | cut -d "." -f2-3` == "cern.ch" ] ; then  
    buffer=$(bjobs 2>/dev/null)
    i=0
    while read line
    do
	if [ $i -ne 0 ] ; then
	    arr=($line)
	    bkill ${arr[0]}
	fi
	((i++))
    done <<< "$buffer"
    
fi