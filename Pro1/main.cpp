#include"main.h"
#include"Dokument.h"
#include<cstdarg>
#include<stdio.h>
#include<iostream>

using namespace std;

int main()
{
	short cmd;//przechowuje wybory uzytkownika cmd-command
	Dokument Kontener;
	short width;//szerokosc
	short line_color[3];
	short interior_color[3];
	short stroke_weight;//grubosc lini
	short local[2];
	bool end=false;// zmienna do wyjscia z petli by nie uzywac goto
	
	string name;//nazwa pliku do ktorego uzytkownik chce zapisac dane
	menu(true);//true bo nie chce wyswietlac calego menu tylko jego czesc. Jak uzytkownik cos doda to false
	bool cond=true;
	while(1)
	{
		check(cmd, "Co teraz ? /2/ wyswietla menu: ",2, -1, 6);
       		switch (cmd)
		{
		case 0:{end=true; break;}// wyjdz
		case 5:{if(Kontener.where==0)break; //gdy nie ma zadnego


			if(choice("Wyswietlic baze ?[y,n]: ")) 
			Kontener.write();
			
			check(cmd, "Ktory ? ID: ", 2, 0, (short)Kontener.where+1); 
			
			Kontener-Kontener.el[cmd-1];// usuwa element przeciazony operator

			if(Kontener.where==0)cond=true;
			break;}// usun
		case 4:{if(Kontener.where==0) break;
			 str(name, "Podaj nazwe pliku (dodaj format svg): ");
			if(/*Kontener.exp(name)*/ Kontener>>name) cout<<"operacja powiodla sie."<<endl;
			else cout<<"Operacja nie powiodla sie."<<endl;
			break;
				}// exportuj
		case 2:{menu(cond); break;}//wyswietl menu
		case 3:{if(Kontener.where==0) break; Kontener.write(); break;}
		case 1://dodawanie elemntu
			{	while(true){
				
				str(name, "Podaj nazwe elementu: ");
				
				check(width, "Podaj szerokosc elementu w pixelach: ", 1, 0);
				
				cout<<"Podaj kolory lini w rgb <0, 255>: "<<endl;
				
				add(line_color);

				cout<<"Podaj kolory wypelnienia w rgb <0, 255>: "<<endl;
				
				add(interior_color);

				check(stroke_weight, "Podaj szerokosc lini w pixelach: ", 1, 0);

				cout<<"Podaj polozenie w pixelach, lewy gorny rog to punkt 0.0"<<endl;
				check(local[0], "x: ", 1, -1);
				check(local[1], "y: ", 1, -1);
				
				/*
				Urzycie wskaźnika:
				nie można użyć malloc bo nie ma możliwości użycia konstruktora
				Element *elem=NULL;
				elem(width, line_color, interior_color, stroke_weight, local, name)=(Element*)malloc(sizeof(Element*));
				wyskoczy błąd przy użyciu konstruktora. Trzeba byłoby napisać jakąś metodę w klasie Element do późniejszej
				inicjalizacji.
				Dlatego uzywamy new:
				*/
				
				Element *elem = new Element((unsigned short)width, (unsigned short*)line_color, (unsigned short*)interior_color, (unsigned short)stroke_weight, (unsigned short*)local, name);
				//zwróć uwagę że po new jest typ 
				cout<<"Specyfikacja nowego elementu: "<<endl;
				elem->write();
				
				if(choice("Zaakceptowac ?[y,n]: "))
				{Kontener+elem; break;}
				
				continue;
				}
				cond=false;//juz jest element 
				break;
			}// dodaj
		}
		if(end)break;
	}
	return 0;
}

bool choice(const char *msg)
{
	string c;

	while(true)// poprawnosc wprowadzonych danych
	{
		cout<<msg;
		getline(cin, c);

		if(cin.fail())continue;
		
		if((c.c_str())[0]=='y' || (c.c_str())[0]=='n'){break;}
		continue;
	}
			
	return (c.c_str())[0]=='y';
}


void str(string &name, const char *msg)
{
	while(true)
	{
		cout<<msg;
		cin>>name;
		if(name.size()<=20 && name.size()>=1)break;
		continue;
	}
}

void check(short &to_check, const char *str, int n, ...)//n ilosc dodatkowych argumentow, pierwszy dod min drugi max.
{
	va_list ap;//tworzy zmienna ap typu va_list 
	va_start(ap, n);//udostępnia parametry znajdujące się po parametrze n
	
	int min, max; //zmienne potrzebne do tego, że va_arg po każdym wywołaniu przesówa wskaźnik o jeden więc w przypadku pomyłki jest 
	//problem
	
	min=va_arg(ap, int);
	if(--n) max=va_arg(ap, int);// gdy chcemy ograniczyc z gory
	
	while(true)
	{	
		cin.clear();

 	        cout<<str;//wyswietla wiadomosc z parametru
		cin>>to_check;//pobiera wartosc do sprawdzenia
		
		if(cin.fail())//jesli blad wprowadzenia

		{
            		while(fgetc(stdin)!='\n');//czyszczenie bufora
            		cin.clear();
            		continue;
		}
		
		if(to_check<=min)
		{continue;}//gdy jest mniejsze od minimum

		if(n)
		if(to_check>=max)
		{continue;}//gdy jest wieksze od max

		break;
	}
	va_end(ap);
	while(cin.get()!='\n');//czyszczenie bufora
	cin.clear();
}

void add(short tab[])
{
	check(tab[0], "red: " , 2, -1, 256);
	check(tab[1], "green: ", 2, -1, 256);
	check(tab[2], "blue: ", 2, -1, 256);
}

void menu(bool condition)
{
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"$ Menu:"<<endl<<"$ 1. Dodaj nowy element /1/"<<endl<<"$ 2. Menu /2/"<<endl;
	if(condition) 
	{
		cout<<"$ 0. Wyjdz /0/"<<endl;
		cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
		return;
	}
	cout<<"$ 3. Wyswietl baze /3/"<<endl;
	cout<<"$ 4. Exportuj do SVG /4/"<<endl<<"$ 5. Usun element /5/"<<endl<<"$ 0. Wyjdz /0/"<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
}
