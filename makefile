Project2: main.o Executive.o Events.o TimeSlots.o Task.o
	g++ -std=c++11 -g -Wall main.o Executive.o Events.o TimeSlots.o Task.o -o Project2

main.o: main.cpp Executive.h
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.h Executive.cpp Events.h LinkedList.h Node.h
	g++ -std=c++11 -g -Wall -c Executive.cpp
	
Events.o: Events.h Events.cpp TimeSlots.h Task.h LinkedList.h
	g++ -std=c++11 -g -Wall -c Events.cpp

TimeSlots.o: TimeSlots.h TimeSlots.cpp
	g++ -std=c++11 -g -Wall -c TimeSlots.cpp

Task.o: Task.h Task.cpp
	g++ -std=c++11 -g -Wall -c Task.cpp
	
clean:
	rm *.o Project2
