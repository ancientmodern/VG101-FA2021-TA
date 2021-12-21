#!/bin/bash

filelist=$(ls data)
cd data
for file in $filelist; do
  if [ ! -f ${file}/P1.cpp ]; then
    echo $file
    cd $file
    my_path=$(find . -name P1.cpp | awk -F '/' '{print $2}')
    cp ${my_path}/P*.cpp .
    cd ..
  fi
done
