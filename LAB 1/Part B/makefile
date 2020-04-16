all : functions 

main.o : main.cpp functions.h
	g++ -c -g main.cpp

functions.o : functions.cpp functions.h
	g++ -c -g functions.cpp

functions: main.o functions.o
	g++ main.o functions.o -o functions

check : all
	./functions

clean : 
	rm -f *.o functions
	rm -f *.o core
	rm -f *.o a.out


