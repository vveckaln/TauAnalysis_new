#! /bin/sh

folder=$FILES"/RunII/FARM/outputs"

ind=0 

while true;
do
    ind_txt=$ind
  
    while [ ${#ind_txt} -ne 4 ]; 
    do 
	ind_txt="0"$ind_txt 
    done
    cat $folder"/"$1"/"$ind_txt"_Analysis_"$1"_$2.txt"
    if [ $? -ne 0 ];
    then
	echo "breaking"
	break
    fi
    echo "Finished file #" $ind
    read -p "Press Enter:"
    ((ind++))
    
done 