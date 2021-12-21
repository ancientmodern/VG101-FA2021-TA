#!/usr/bin/bash
rm -rf out
mkdir out

g++ -O2 -Wall -Wextra -pedantic -std=c++11 P1.cpp -o out/P1 2>> out/log.txt
g++ -O2 -Wall -Wextra -pedantic -std=c++11 P2.cpp -o out/P2 2>> out/log.txt
g++ -O2 -Wall -Wextra -pedantic -std=c++11 P3.cpp -o out/P3 2>> out/log.txt
g++ -O2 -Wall -Wextra -pedantic -std=c++11 P4.cpp -o out/P4 2>> out/log.txt
g++ -O2 -Wall -Wextra -pedantic -std=c++11 P5.cpp -o out/P5 2>> out/log.txt

if [ -s out/log.txt ]; then
	echo "have warning(s) or error(s):"
	echo " "
	cat out/log.txt
else
	echo "no warning, OK"
	rm out/log.txt
fi
