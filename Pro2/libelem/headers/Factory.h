#include"Element.h"
#include<iostream>
#include "My_types.h"

#ifndef FACTORY_H
#define FACTORY_H

class Factory {

    static unsigned int ID_;//po co ID w fabryce
    static Factory factory_;//co to
    //mapa przechowujaca pary id - klasy, wskaznik na funcje tworzaca obiekt
    //jej definicja w pliku naglowkowym My_types.h
    My_map Element_creators_;
    Factory(){};//prywatny konstruktor pusty uniemozliwia stworzenie obiektu bez urzycia getInstance

public:

    static Factory & getInstance(){return factory_;};//czemu zwracana referencja
    unsigned int registerElement(CreateElement fun);
    void read_data(std::ifstream &input, My_vector &v );
    Element *Create(unsigned id);
};

#endif
