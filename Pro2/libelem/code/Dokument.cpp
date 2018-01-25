#include"../headers/Dokument.h"
#include<string.h>
#include<iostream>

using namespace std;

bool Dokument::exp_to_txt(std::string &name_file)throw(bool&)
{
    int size=container.size();
    it_el=container.begin();

    ofstream file(name_file.c_str(), ios::trunc | ios::out);

    /*trzeba sprawdzic czy pliki zostaly otworzone obie funkcje zwracaja true gdy uzyskalem dostep do pliku.
    zalezy tez od parametrow otwarcia gdy mam dostep tylko do odczytu a zechce pisac to zostanie ustawiona odpowiednia flaga*/
    if(file.is_open()==false || file.good()==false)
        throw false;

    for(int i=0; i<size; i++)
        it_el[i]->exp_to_txt(file);

    file.close();

    return true;
}

bool Dokument::imp_from_txt(std::string &name_file, Factory &f)throw(bool&)
{
    it_el=container.begin();

    ifstream file(name_file.c_str(), ios::in);

    /*trzeba sprawdzic czy pliki zostaly otworzone obie funkcje zwracaja true gdy uzyskalem dostep do pliku.*/

    if(file.is_open()==false || file.good()==false)
        throw false;

    f.read_data(file, container);

    file.close();

    return true;
}

Dokument Dokument::operator+(Element *el_to_add)
{
	this->container.push_back(el_to_add);
	return *this;
}

void Dokument::write_in_terminal()//wypisuje wszystkie elementy w terminalu
{
	this->it_el=container.begin();
	int size=container.size();
	for(int i=0; i<size; i++)
	{
		cout<<i+1<<".";
        it_el[i]->write_in_terminal();
	}
}
Dokument Dokument::operator-(int i)//przyjmuje ity elemnt 3 to 3
{
	this->container.erase(container.begin()+i-1);//wiec minus 1
	return *this;
}

bool Dokument::operator>>(string name_file)throw(bool&)
{	
	/*mamy stringa i chcemy z niego zrobic napis czyli char* to .c_str() trunc zeruje zawartosc podczas zapisu out umozliwia zapis
	in odczyt ate/app zapis na koncu*/
	ofstream file(name_file.c_str(), ios::trunc | ios::out);
	
	/*trzeba sprawdzic czy pliki zostaly otworzone obie funkcje zwracaja true gdy uzyskalem dostep do pliku.
	zalezy tez od parametrow otwarcia gdy mam dostep tylko do odczytu a zechce pisac to zostanie ustawiona odpowiednia flaga*/
    if(file.is_open()==false || file.good()==false)
        throw false;

	file<<"<svg"<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;

	this->it_el=container.begin();

	int size=container.size();
	for(int i=0; i<size; i++)
	{
        it_el[i]->exp_to_svg(file);
	}
	file<<"</svg>";
	
	file.close();
	
	return true;
}

