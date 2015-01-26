#!/bin/bash


# "grep vischia" selects only the lines corresponding to a job. It might as well be "grep job-" or stuff like that.
user=`whoami`
while true ;
 do
  echo "running: " `qstat -u $user | grep $user | grep " r " | wc -l` "    total: " `qstat -u $user | grep $user | wc -l` 


done