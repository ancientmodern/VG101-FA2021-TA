#!/bin/bash

res="/mnt/d/JI/VG101/Grade/Mid2/result.csv" # change to your own path
echo "name,sid,P1,P2,P3,P4,P5" >$res

files=$(ls data)
cd data || exit

for file in $files; do
  echo -n "$(echo "$file" | grep -oE "^[a-z]+")," >>$res   # name
  echo -n "$(echo "$file" | grep -oE "[0-9]{12}")," >>$res # sid
  cd "$file" || exit
  # problem 1 to 4
  for i in {1..4}; do
    score=0
    name="P$i"
    gcc -O2 -o $name "${name}.c" -lm
    path="/mnt/d/JI/VG101/Grade/Mid2/${name}/pretest"
    mv $name $path
    for j in {0..9}; do
      timeout 1 ${path}/${name} <"${path}/case${j}.in" >"${path}/res${j}.out"
      #      tr -d '\n' <"${path}/res${j}.out" >"${path}/temp_res${j}.out"
      #      tr -d '\n' <"${path}/case${j}.out" >"${path}/temp_case${j}.out"

      # ignore all white spaces (space, \n, tab...)
      if diff -w "${path}/res${j}.out" "${path}/case${j}.out"; then
        ((score = score + 2))
      fi
      rm -rf "${path}/res${j}.out"
    done
    echo -n "${score}," >>$res
    rm -rf ${path}/${name}
  done
  
  # problem 5
  score=0
  gcc -O2 -o P5 "P5.c" -lm
  path="/mnt/d/JI/VG101/Grade/Mid2/P5/case"
  for j in {0..9}; do
    cp P5 "${path}${j}"
    cd "${path}${j}" || exit
    timeout 2 "${path}${j}/P5" >"${path}${j}/res.out"

    # separate mean and median, each worth 1 point
    grep -oE "\-*[0-9]+\.[0-9]{6}" "${path}${j}/res.out" | awk 'NR == 1 {print}' >"${path}${j}/mean_res.out"
    grep -oE "\-*[0-9]+\.[0-9]{6}" "${path}${j}/res.out" | awk 'NR == 2 {print}' >"${path}${j}/median_res.out"
    grep -oE "\-*[0-9]+\.[0-9]{6}" "${path}${j}/P5.out" | awk 'NR == 1 {print}' >"${path}${j}/mean_p5.out"
    grep -oE "\-*[0-9]+\.[0-9]{6}" "${path}${j}/P5.out" | awk 'NR == 2 {print}' >"${path}${j}/median_p5.out"
    if diff -w "${path}${j}/mean_res.out" "${path}${j}/mean_p5.out"; then
      ((score = score + 1))
    fi
    if diff -w "${path}${j}/median_res.out" "${path}${j}/median_p5.out"; then
      ((score = score + 1))
    fi
    rm -rf "${path}${j}/P5" "${path}${j}/res.out" "${path}${j}/mean_res.out" "${path}${j}/median_res.out" "${path}${j}/mean_p5.out" "${path}${j}/median_p5.out"
    cd - || exit
  done
  echo "${score}" >>$res
  rm -rf P5
  cd ..
done
