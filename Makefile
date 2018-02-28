Project1: main.o Path.o Highlight.o Designs.o 
	g++ -std=c++11 -g -Wall main.o Path.o Highlight.o Designs.o -o Project1 -lncurses
main.o: main.cpp 
	g++ -std=c++11 -g -Wall -c main.cpp
Path.o: Path.cpp Path.h Highlight.h
	g++ -std=c++11 -g -Wall -c Path.cpp
Highlight.o: Highlight.cpp Highlight.h
	g++ -std=c++11 -g -Wall -c Highlight.cpp
Designs.o: Designs.cpp Designs.h 
	g++ -std=c++11 -g -Wall -c Designs.cpp
clean:
	rm *.o Project1
