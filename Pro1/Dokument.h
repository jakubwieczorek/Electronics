
#include<string>
#include<fstream>
#include"Element.h"


class Dokument {
 enum {size=100};
public:
 unsigned short where;
 Element *el[size];
 Dokument();//konstruktor
 bool isFull();
 void operator+(Element *el_to_dod);//dodawanie elemntu
 void operator-(Element* &to_del);//usuwanie elemntu
 void write();//wypisanie wszystkich elementow w terminalu
 bool operator>>(std::string name_file);//export do pliku svg o nazwie name_file

};


