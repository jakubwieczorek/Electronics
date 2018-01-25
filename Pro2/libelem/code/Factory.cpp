#include"../headers/Factory.h"
#include"../headers/Ftransistor.h"
#include"../headers/Cdiode.h"

using namespace std;

unsigned int Factory::registerElement(CreateElement fun)
{
    //metoda automatycznie zwieksza licznikk ID_ i
    //zapisuje pare
    Element_creators_.insert(std::pair<unsigned int,CreateElement>(++ID_,fun)); //###
    //wynik zwracany przechowywany przez kazda klase w polu statycznym id_
    return ID_;
}

Element * Factory::Create(unsigned id)
{
    //Metoda  na  podstawie id tworzy nowy obiekt
    My_map::iterator it=Element_creators_.find(id);
    if(it!=Element_creators_.end())
    {
        return (it->second)();//wywolanie metody fun z ###
    }
    return NULL;
}

void Factory::read_data(std::ifstream &input, My_vector & v)
{
    unsigned int ID;
    Element *tempElement;
    while(!input.eof())
    {
        //odczytujemy id_ klasy
        input>>ID;
        //tu tworzymy nowy obiekt
        if(input.eof()) return;
        tempElement=Create(ID);
        if(tempElement!=NULL)
        {
            //odczytanie danych juz do konkretnego obiektu
            tempElement->imp_from_txt(input);
            //wczytany obiekt (tak naprawde wskaznik do niego) umieszczamy w wektorze
            v.push_back(tempElement);
        }
    }
}

unsigned int Factory::ID_=1;
Factory Factory::factory_;
