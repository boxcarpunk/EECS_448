Project1: main.o Executive.o Events.o TimeSlots.o Task.o Path.o Highlight.o Designs.o 
	g++ -std=c++11 -g -Wall main.o Executive.o Events.o TimeSlots.o Task.o Path.o Highlight.o Designs.o -o Project1 -lncurses

main.o: main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.h Executive.cpp Events.h LinkedList.h Node.h
	g++ -std=c++11 -g -Wall -c Executive.cpp
	
Events.o: Events.h Events.cpp TimeSlots.h Task.h LinkedList.h
	g++ -std=c++11 -g -Wall -c Events.cpp

TimeSlots.o: TimeSlots.h TimeSlots.cpp
	g++ -std=c++11 -g -Wall -c TimeSlots.cpp

Task.o: Task.h Task.cpp
	g++ -std=c++11 -g -Wall -c Task.cpp

Path.o: Path.cpp Path.h Highlight.h
	g++ -std=c++11 -g -Wall -c Path.cpp
	
Highlight.o: Highlight.cpp Highlight.h
	g++ -std=c++11 -g -Wall -c Highlight.cpp
	
Designs.o: Designs.cpp Designs.h 
	g++ -std=c++11 -g -Wall -c Designs.cpp
	
clean:
	rm *.o Project1