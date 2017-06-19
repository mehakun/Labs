COMPILER = g++
CCFLAGS = -std=c++1z -Wall -Werror -pedantic -O2
prog: learn.o classify.o main.o
	$(COMPILER) $(CCFLAGS) -o $@ learn.o classify.o main.cpp

main.o: main.cpp 
	$(COMPILER) $(CCFLAGS) main.cpp -c

learn.o: ./src/learn.cpp
	$(COMPILER) $(CCFLAGS) ./src/learn.cpp -c

classify.o: ./src/classify.cpp
	$(COMPILER) $(CCFLAGS) ./src/classify.cpp -c

clear:
	rm -rf *.o prog
