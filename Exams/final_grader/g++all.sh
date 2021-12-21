#!/usr/bin/bash

# Check compile error and warning
for d in `ls`
do
	if [ $d != "g++all" ]; then
	echo $d
	cd $d
	if [ $? = 0 ]; then
	bash makeF
	cd ..
	fi
	fi
	if [ ! -f "$d/out/log.txt" ]; then
		echo $d 1>>"no warning list.txt"
	else
		echo $d 1>>"have warning.txt"
	fi
done

