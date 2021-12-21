#!/bin/bash

res="/mnt/d/JI/VG101/Grade/Final/result.csv"
echo "name,sid,P1,P2,P3" >$res
# echo "name,sid,1,2,3,4,5,6,7,8,9,10,11,12,13,score" >$res

files=$(ls data)
cd data || exit

# set -x

for file in $files; do
  echo -n "$(echo "$file" | grep -oE "^[a-z]+")," >>$res
  echo -n "$(echo "$file" | grep -oE "[0-9]{12}")," >>$res
  cd "$file" || exit
  # problem 1 to 2
  for i in {1..2}; do
    score=0
    name="P$i"
    g++ -O2 -o $name "${name}.cpp" -lm
    path="/mnt/d/JI/VG101/Grade/Final/${name}"
    mv $name $path
    for j in {0..9}; do
      timeout 1 ${path}/${name} <"${path}/case${j}.in" >"${path}/res${j}.out"

      # ignore all white spaces (space, \n, tab...)
      if diff -w "${path}/res${j}.out" "${path}/case${j}.out"; then
        ((score = score + 2))
      fi
      rm -f "${path}/res${j}.out"
    done
    echo -n "${score}," >>$res
    rm -f ${path}/${name}
  done
  # problem 3
  score=0
  for i in {1..5}; do
    path="/mnt/d/JI/VG101/Grade/Final/P3/$i"
    g++ -O2 -o ${path}/P3 P3.cpp -lm
    cd ${path}
    ./P3 >"${path}/res.out"
    if diff -w "${path}/res.out" "${path}/P3.out"; then
      ((score = score + 4))
    fi
    rm -f P3 "${path}/res.out"
    cd -
  done
  echo -n "${score}," >>$res
  # problem 5
  # score=0
  # name="P5"
  # g++ -O2 -o $name "${name}.cpp" -lm
  # path="/mnt/d/JI/VG101/Grade/Final/${name}"
  # mv $name $path
  # for j in {0..12}; do
  #   timeout 0.2 ${path}/${name} <"${path}/case${j}.in" >"${path}/res${j}.out"

  #   # ignore all white spaces (space, \n, tab...)
  #   if diff -w "${path}/res${j}.out" "${path}/case${j}.out"; then
  #     ((score = score + 1))
  #     echo -n "Correct, " >> $res
  #   else 
  #     echo -n "Wrong, " >> $res
  #   fi
  #   rm -f "${path}/res${j}.out"
  # done
  # echo "${score}" >>$res
  # rm -f ${path}/${name}
  cd ..
done
