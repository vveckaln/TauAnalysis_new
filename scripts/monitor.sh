#!/bin/bash


# "grep vischia" selects only the lines corresponding to a job. It might as well be "grep job-" or stuff like that.
user=`whoami`
echo "RUNNING        PENDING"
if [ `hostname | cut -d "." -f2-4` == "ncg.ingrid.pt" ] ; then  

    while true ;
    do
	echo "running: " `qstat -u $user | grep $user | grep " r " | wc -l` "    total: " `qstat -u $user | grep $user | wc -l` 


    done

elif [ `hostname | cut -d "." -f2-3` == "cern.ch" ] ; then  
    while true ;
    do
        
	#berr=$(bjobs > buffer 2>&1 )
        buffer=$(bjobs 2> /dev/null )
	i=0
	R=0
	P=0
	while read line ; 
	do
	    if [ $i -ne 0 ] ; then
		arr=($line)
		var=${arr[2]}
		#echo "dtag "$dtag
		if [ "$var" == "RUN" ] ; then
			((R++))
		elif [ "$var" == "PEND" ] ; then
			((P++))
		fi
		
	    fi
	    ((i++))
	done <<< "$buffer" #so-called "here variable"

	echo $R"       "$P
    done
fi


