main.out: main.o Element.o Dokument.o
	g++ -g -std=c++11 -o main.out main.o Element.o Dokument.o
main.o: main.cpp main.h Dokument.h Element.h
	g++ -g -std=c++11 -c -Wall -o main.o main.cpp
Element.o: Element.cpp Dokument.h Element.h
	g++ -g -std=c++11 -c -Wall -o Element.o Element.cpp
Dokument.o: Dokument.cpp Dokument.h Element.h
	g++ -g -std=c++11 -c -Wall -o Dokument.o Dokument.cpp
