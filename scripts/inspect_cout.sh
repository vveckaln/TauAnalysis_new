#! /bin/sh

folder="/afs/cern.ch/work/v/vveckaln/private/RunII/FARM/outputs"

ind=0 

while true;
do
    ind_txt=$ind
  
    while [ ${#ind_txt} -ne 4 ]; 
    do 
	ind_txt="0"$ind_txt 
    done
    cat $folder"/"$ind_txt"_"$1".cout"
    if [ $? -ne 0 ];
    then
	echo "breaking"
	break
    fi
    echo "Finished file #" $ind
    read -p "Press Enter:"
    ((ind++))
    
done 