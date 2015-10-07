#! /bin/bash

for ind in {0..100}
do
    cat xrdcp_test$ind.txt
    echo "read file xrdcp_test"$ind".txt"
    read -p "press Enter " -n1 -s
done