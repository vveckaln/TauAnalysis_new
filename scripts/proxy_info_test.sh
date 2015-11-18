!# /bin/sh

for file in /lstore/cms/viesturs/RunII/FARM/outputs/proxy_test/*.txt 
do
    cat $file
    read -p "Press Enter"
done


