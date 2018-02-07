project1: main.o Executive.o Events.o
	g++ -std=c++11 -g -Wall main.o Executive.o Events.o -o project1

main.o: main.cpp Executive.h Events.h LinkedList.h Node.h Events.cpp LinkedList.hpp Node.hpp
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.h Executive.cpp LinkedList.h Node.h Events.h
	g++ -std=c++11 -g -Wall -c Executive.cpp Events.cpp

Events.o: Events.h Events.cpp
	g++ -std=c++11 -g -Wall -c Events.cpp

clean:
	rm *.o project1
	rm *.o main
	rm *.o Executive
	rm *.o Events
