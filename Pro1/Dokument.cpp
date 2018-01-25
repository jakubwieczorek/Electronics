#include"Dokument.h"
#include<string.h>
#include<iostream>

using namespace std;

bool Dokument::isFull()
{
	return *(el+size-1)!=NULL;
}

Dokument::Dokument()
{
	for(int i=0; i<size; i+=1){*(el+i)=NULL;}//wyzerowanie calej tablicy
	where=0;
}

void Dokument::operator+(Element *el_to_dod)
{
	if(!isFull()) el[where++]=el_to_dod;
	else cout<<"Brak miejsca na dodanie nowego elemntu."<<endl;

}

void Dokument::write()//wypisuje wszystkie elemntu w terminalu
{
	int i;
	for(i=0; el[i]!=NULL ;i++)
		{cout<<i+1<<".";
		el[i]->write();}
}
void Dokument::operator-(Element* & to_del)
{
	to_del=el[--where];
	el[where]=NULL;
}

bool Dokument::operator>>(string name_file)
{	
//	unsigned short maxx=0;
//	unsigned short sumax=0;
//	unsigned short maxy=0;
//	unsigned short sumay=0;
	
	ofstream file(name_file.c_str(), ios::trunc | ios::out);
	
	if(file.is_open()==false || file.good()==false) return false;

//	for(int i=0; el[i]!=NULL; i++) {if((sumax=el[i]->width+el[i]->local[0])>maxx) maxx=sumax;
//	if((sumay=el[i]->local[1]+el[i]->width)>maxy) maxy=sumay;}
//	maxx+=100;
//	maxy+=100;
//	file<<"<svg width=\""<<maxx<<"\"  height=\""<<maxy<<"\" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
	file<<"<svg"<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;

	for(int i=0; el[i]!=NULL; i++) el[i]->draw(file);//petla po wszystkich elemntach

	file<<"</svg>";
	
	file.close();
	
	return true;
}

