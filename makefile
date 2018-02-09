project1: main.o Executive.o Events.o TimeSlots.o
	g++ -std=c++11 -g -Wall main.o Executive.o Events.o TimeSlots.o -o project1

main.o: main.cpp Executive.h
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.h Executive.cpp Events.h LinkedList.h Node.h
	g++ -std=c++11 -g -Wall -c Executive.cpp

Events.o: Events.h Events.cpp TimeSlots.h LinkedList.h
	g++ -std=c++11 -g -Wall -c Events.cpp

TimeSlots.o: TimeSlots.h TimeSlots.cpp
	g++ -std=c++11 -g -Wall -c TimeSlots.cpp

clean:
	rm *.o project1
