#!/bin/bash

filelist=$(ls data)
cd data
for file in $filelist; do
  if [ ! -f ${file}/P1.c ]; then
    echo $file
    cd $file
    my_path=$(find . -name P1.c | awk -F '/' '{print $2}')
    cp ${my_path}/P*.c .
    cd ..
  fi
done
