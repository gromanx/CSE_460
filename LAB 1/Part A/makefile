all : greet

main.o : main.cpp greet.h
	g++ -c -g main.cpp

greet.o : greet.cpp greet.h
	g++ -c -g greet.cpp

greet : main.o greet.o
	g++ main.o greet.o -o greet

check : all
	./greet

clean : 
	rm -f *.o greet
