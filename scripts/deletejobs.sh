#!/bin/bash


user=`whoami`

var=$( qstat -u $user | grep -oE "[[:digit:]]{7}")

  
for i in ${var[@]} 
do
    echo $i
    qdel $i
done