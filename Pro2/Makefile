TARGET = Projekt2.out
LIBS = $(SUBLIBS) -L /home/jakub/Dokumenty/C++/Projekt2/libelem -lelem
OBJECTS = Projekt2.o 
INCPATH = -I /home/jakub/Dokumenty/C++/Projekt2/libelem/headers/
LINK = g++
CXX = g++
FLAGS = -std=c++11 -g -Wall -c
LFLAGS = -Wl,-z,origin -Wl,-rpath,\$$LD_LIBRARY_PATH
# nie dziala trzeba z paluszka VARIABLE = export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:../Projekt2/libelem 

$(TARGET): $(OBJECTS)
	$(LINK) -o $(TARGET) $(OBJECTS) $(LIBS)
Projekt2.o: Projekt2.cpp ../Projekt2/libelem/headers/Dokument.h main.h
	$(CXX) $(FLAGS) $(INCPATH) -o Projekt2.o Projekt2.cpp
clean:
	rm -f *.o 
	rm *.out
Change:
	$(VARIABLE)
