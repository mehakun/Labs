all:
	g++ vector.cpp sort.cpp main.cpp -pedantic -g -std=c++11 -o RadixSort

clean:
	rm -rf *~ *gch RadixSort

tar:	
	tar -cf RadixSort.tar ../RadixSort/

bench:
	g++ vector.cpp sort.cpp bench.cpp -pedantic -std=c++11 -o Bench
