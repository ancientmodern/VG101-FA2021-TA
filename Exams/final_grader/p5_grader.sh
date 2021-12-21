#!/bin/bash

res="/mnt/d/JI/VG101/Grade/Final/p5.csv"
# echo "name,sid,P1,P2,P3" >$res
echo "name,sid,1,2,3,4,5,6,7,8,9,10,11,12,13,score" >$res

files=$(ls data)
cd data || exit

# set -x

for file in $files; do
  echo -n "$(echo "$file" | grep -oE "^[a-z]+")," >>$res
  echo -n "$(echo "$file" | grep -oE "[0-9]{12}")," >>$res
  cd "$file" || exit
  # problem 5
  score=0
  name="P5"
  g++ -O2 -o $name "${name}.cpp" -lm
  path="/mnt/d/JI/VG101/Grade/Final/${name}"
  mv $name $path
  for j in {0..12}; do
    timeout 0.2 ${path}/${name} <"${path}/case${j}.in" >"${path}/res${j}.out"
    # ignore all white spaces (space, \n, tab...)
    if diff -w "${path}/res${j}.out" "${path}/case${j}.out"; then
      ((score = score + 1))
      echo -n "Correct, " >> $res
    else 
      echo -n "Wrong, " >> $res
    fi
    rm -f "${path}/res${j}.out"
  done
  echo "${score}" >>$res
  rm -f ${path}/${name}
  cd ..
done
