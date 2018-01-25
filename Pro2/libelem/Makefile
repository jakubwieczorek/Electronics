TARGET = libelem.so.1.0.1 
OBJECTS = D_LCCdiode.o D_SpinFtransistor.o D_Dokument.o D_Ftransistor.o D_Cdiode.o D_Factory.o 
LINK = g++ 
LFLAGS = -shared -Wl,-soname,libelem.so.1 #Dla library -shared czyli wspoldzielona biblioteka -Wl to instrukcje dla linkera
OFLAGS =  -fPIC -std=c++11 -g -Wall -c #Dla plikow .o -fPIC tworzy relokowany kod, czyli taki, ze moze byc zaladowany w dowolny obszar pamieci
CXX = g++

$(TARGET): $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS)
D_SpinFtransistor.o: ../libelem/code/SpinFtransistor.cpp ../libelem/headers/SpinFtransistor.h
	$(CXX) $(OFLAGS) -o D_SpinFtransistor.o ../libelem/code/SpinFtransistor.cpp
D_LCCdiode.o: ../libelem/code/LCCdiode.cpp ../libelem/headers/LCCdiode.h
	$(CXX) $(OFLAGS) -o D_LCCdiode.o ../libelem/code/LCCdiode.cpp
D_Factory.o: ../libelem/code/Factory.cpp ../libelem/headers/Factory.h
	$(CXX) $(OFLAGS) -o D_Factory.o ../libelem/code/Factory.cpp
D_Dokument.o: ../libelem/code/Dokument.cpp ../libelem/headers/Dokument.h
	$(CXX) $(OFLAGS) -o D_Dokument.o ../libelem/code/Dokument.cpp
D_Ftransistor.o: ../libelem/code/Ftransistor.cpp ../libelem/headers/Ftransistor.h
	$(CXX) $(OFLAGS) -o D_Ftransistor.o ../libelem/code/Ftransistor.cpp
D_Cdiode.o: ../libelem/code/Cdiode.cpp ../libelem/headers/Cdiode.h
	$(CXX) $(OFLAGS) -o D_Cdiode.o ../libelem/code/Cdiode.cpp
clean:
	rm -f *.o
