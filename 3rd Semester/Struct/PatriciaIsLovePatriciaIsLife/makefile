
all:	
	g++ main.cpp patricia.cpp -std=c++11 -pedantic -Wall -o PatriciaIsLovePatriciaIsLife	
gprof:
	g++ main.cpp patricia.cpp -std=c++11 -pedantic -pg -Wall -o PatriciaIsLovePatriciaIsLife
bench:
	g++ bench.cpp patricia.cpp -std=c++11 -pedantic -pg -Wall -o benchmark
clear:
	rm -rf PatriciaIsLovePatriciaIsLife gmon.out *~
