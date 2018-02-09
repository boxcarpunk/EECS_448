project1: main.o Executive.o Events.o TimeSlots.o
	g++ -std=c++11 -g -Wall main.o Executive.o Events.o TimeSlots.o -o project1

main.o: main.cpp Executive.h Events.h LinkedList.h Node.h TimeSlots.h Events.cpp LinkedList.hpp Node.hpp TimeSlots.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.h Executive.cpp LinkedList.h Node.h Events.h
	g++ -std=c++11 -g -Wall -c Executive.cpp

Events.o: Events.h Events.cpp TimeSlots.h TimeSlots.cpp 
	g++ -std=c++11 -g -Wall -c Events.cpp 

TimeSlots.o: TimeSlots.h TimeSlots.cpp
	g++ -std=c++11 -g -Wall -c TimeSlots.cpp

clean:
	rm *.o project1
	rm *.o main
	rm *.o Executive
	rm *.o Events
	rm *.o TimeSlots
