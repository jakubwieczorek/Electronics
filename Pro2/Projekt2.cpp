#include"main.h"
#include<Dokument.h>
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
    short stroke_width;//grubosc lini
	short local[2];
    short spin;
	bool end=false;// zmienna do wyjscia z petli by nie uzywac goto

	string name;//nazwa pliku do ktorego uzytkownik chce zapisac dane
	menu(true);//true bo nie chce wyswietlac calego menu tylko jego czesc. Jak uzytkownik cos doda to false
	bool cond=true;

    Factory & f1=Factory::getInstance();//nie mozna zrobic Factory f1; i tyle ?
    //Rejestracja class w fabryce

    Ftransistor::ID=f1.registerElement(Ftransistor::CreateFtransistor);
    Cdiode::ID=f1.registerElement(Cdiode::CreateCdiode);
    SpinFtransistor::ID=f1.registerElement(SpinFtransistor::CreateSpinFtransistor);
    LCCdiode::ID=f1.registerElement(LCCdiode::CreateLCCdiode);

	while(1)
	{
        check(cmd, "Co teraz ? /2/ wyswietla menu: ",2, -1, 9);
       	switch (cmd)
		{
		case 0:{end=true; break;}// wyjdz
        case 5:{

            if(Kontener.container.size()==0)break; //gdy nie ma zadnego

			if(choice("Wyswietlic baze ?[y,n]: "))
            Kontener.write_in_terminal();

			check(cmd, "Ktory ? ID: ", 2, 0, Kontener.container.size()+1);

            Kontener=Kontener-cmd;// usuwa element przeciazony operator

			if(Kontener.container.size()==0)cond=true;
			break;}// usun
        case 4:
            {
                if(Kontener.container.size()==0) break;
                str(name, "Podaj nazwe pliku (dodaj format svg): ");
                try
                {
                    if(Kontener>>name) cout<<"operacja powiodla sie."<<endl;
                }
                catch(bool&)
                {
                    cout<<"Operacja nie powiodla sie."<<endl;
                }
                break;
            }// exportuj
		case 2:{menu(cond); break;}//wyswietl menu
        case 6:
            {
                if(Kontener.container.size()==0) break;
                str(name, "Podaj nazwe pliku (dodaj format txt): ");
                try
                {
                    if(Kontener.exp_to_txt(name)) cout<<"operacja powiodla sie."<<endl;
                }
                catch(bool&)
                {
                    cout<<"Operacja nie powiodla sie."<<endl;
                }
                break;
            }
        case 7:
            {
                str(name, "Podaj nazwe pliku (dodaj format txt): ");
                try
                {
                    if(Kontener.imp_from_txt(name, f1)) cout<<"operacja powiodla sie."<<endl;
                }
                catch(bool&)
                {
                    cout<<"Operacja nie powiodla sie."<<endl;
                }

                if(Kontener.container.size()!=0) cond=false;
                break;
            }
        case 3:{if(Kontener.container.size()==0) break; Kontener.write_in_terminal(); break;}
        case 8:
            {
                bool end=false;
                if(choice("Wyswietlic baze ?[y,n]: "))
                Kontener.write_in_terminal();

                int size=Kontener.container.size();
                short cmd2;

                check(cmd2, "Ktory ? ID: ", 2, 0, size+1);
                cmd2--;
                if(Kontener.it_el[cmd2]->show_ID()==2 || Kontener.it_el[cmd2]->show_ID()==4)
                {
                    while(1)
                    {
                        if(end) break;
                        check(cmd, "Ktora skladowa ? (liczac od gory): ", 2, 0, 8);
                        switch(cmd)
                        {
                        case 1:
                            {
                                str(name, "Podaj nazwe elementu: ");
                                static_cast<Ftransistor*>(Kontener.it_el[cmd2])->set_name(name);
                                end=true;
                                break;
                            }
                        case 2:
                            {
                                check(width, "Podaj szerokosc elementu w pixelach: ", 1, 0);
                                Kontener.it_el[cmd2]->set_width(width);
                                end=true;
                                break;
                            }
                        case 3:
                            {
                                check(stroke_width, "Podaj szerokosc lini w pixelach: ", 1, 0);
                                static_cast<Ftransistor*>(Kontener.it_el[cmd2])->set_stroke_width(stroke_width);
                                end=true;
                                break;
                            }
                        case 4:
                            {
                                cout<<"Podaj kolory lini w rgb <0, 255>: "<<endl;
                                add(line_color);
                                static_cast<Ftransistor*>(Kontener.it_el[cmd2])->set_line_color((short unsigned*)line_color);
                                end=true;
                                break;
                            }
                        case 5:
                            {
                                cout<<"Podaj kolory wypelnienia w rgb <0, 255>: "<<endl;
                                add(interior_color);
                                Kontener.it_el[cmd2]->set_interior_color((short unsigned*)interior_color);
                                end=true;
                                break;
                            }
                        case 6:
                            {
                                cout<<"Podaj polozenie w pixelach, lewy gorny rog to punkt 0.0"<<endl;
                                check(local[0], "x: ", 1, -1);
                                check(local[1], "y: ", 1, -1);
                                Kontener.it_el[cmd2]->set_local((short unsigned*)local);
                                end=true;
                                break;
                            }
                        case 7:
                            {
                                if(Kontener.it_el[cmd2]->show_ID()==2) break;
                                check(spin, "Podaj obrot: ", 1, -1);
                                spin=spin%360;
                                static_cast<SpinFtransistor*>(Kontener.it_el[cmd2])->set_spin(spin);
                                end=true;
                                break;
                            }
                        }
                    }
                }
                else if(Kontener.it_el[cmd2]->show_ID()==3 || Kontener.it_el[cmd2]->show_ID()==5)
                {
                    while(1)
                    {
                        if(end) break;
                        check(cmd, "Ktora skladowa ? (liczac od gory): ", 2, 0, 8);
                        switch(cmd)
                        {
                        case 1:
                            {
                                check(width, "Podaj szerokosc elementu w pixelach: ", 1, 0);
                                Kontener.it_el[cmd2]->set_width(width);
                                end=true;
                                break;
                            }
                        case 2:
                            {
                                cout<<"Podaj kolory wypelnienia w rgb <0, 255>: "<<endl;
                                add(interior_color);
                                Kontener.it_el[cmd2]->set_interior_color((short unsigned*)interior_color);
                                end=true;
                                break;
                            }
                        case 5:
                            {
                                if(Kontener.it_el[cmd2]->show_ID()==3) break;
                                cout<<"Podaj kolory lini w rgb <0, 255>: "<<endl;
                                add(line_color);
                                static_cast<LCCdiode*>(Kontener.it_el[cmd2])->set_line_color((short unsigned*)line_color);
                                end=true;
                                break;
                            }
                        case 4:
                            {
                                check(spin, "Podaj obrot: ", 1, -1);
                                spin=spin%360;
                                static_cast<Cdiode*>(Kontener.it_el[cmd2])->set_spin(spin);
                                end=true;
                                break;
                            }
                        case 3:
                            {
                                cout<<"Podaj polozenie w pixelach, lewy gorny rog to punkt 0.0"<<endl;
                                check(local[0], "x: ", 1, -1);
                                check(local[1], "y: ", 1, -1);
                                Kontener.it_el[cmd2]->set_local((short unsigned*)local);
                                end=true;
                                break;
                            }
                        }
                    }
                }

                break;
            }
		case 1://dodawanie elemntu
			{	while(true){
                menuadd();
                check(cmd, "Co teraz ? ",2, 0, 5);

                if(cmd==2 || cmd==3)
                {
                    str(name, "Podaj nazwe elementu: ");

                    cout<<"Podaj kolory lini w rgb <0, 255>: "<<endl;

                    add(line_color);

                    check(stroke_width, "Podaj szerokosc lini w pixelach: ", 1, 0);
                }
                if(cmd==1 || cmd==3 || cmd==4)
                {
                    check(spin, "Podaj obrot: ", 1, -1);
                    spin=spin%360;
                }
                if(cmd==4)
                {
                    cout<<"Podaj kolory lini w rgb <0, 255>: "<<endl;

                    add(line_color);
                }

                check(width, "Podaj szerokosc elementu w pixelach: ", 1, 0);

				cout<<"Podaj kolory wypelnienia w rgb <0, 255>: "<<endl;

				add(interior_color);

				cout<<"Podaj polozenie w pixelach, lewy gorny rog to punkt 0.0"<<endl;
				check(local[0], "x: ", 1, -1);
                check(local[1], "y: ", 1, -1);

                Element *elem;

                if(cmd==2)
                {
                    elem = new Ftransistor((unsigned short)width, (unsigned short*)line_color, (unsigned short*)interior_color, (unsigned short)stroke_width, (unsigned short*)local, name);
                }

                else if(cmd==1)
                {
                    elem = new Cdiode((unsigned short)width, (unsigned short*)interior_color, (unsigned short*)local, (unsigned short)spin);
                }

                else if(cmd==3)
                {
                    elem = new SpinFtransistor((unsigned short)width, (unsigned short*)line_color, (unsigned short*)interior_color, (unsigned short)stroke_width, (unsigned short*)local, name, (unsigned short)spin);
                }

                else if(cmd==4)
                {
                    elem = new LCCdiode((unsigned short)width, (unsigned short*)interior_color, (unsigned short*)local, (unsigned short)spin, (unsigned short*)line_color);
                }

                //zwróć uwagę że po new jest typ
				cout<<"Specyfikacja nowego elementu: "<<endl;

                elem->write_in_terminal();

				if(choice("Zaakceptowac ?[y,n]: "))
				{Kontener=Kontener+elem; break;}

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

void menuadd()
{
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    cout<<"$ 1. Diode pojemnosciowa: /1/"<<endl<<"$ 2. Fototranzystor: /2/"<<endl<<"$ 3. Fototranzystor z obrotem: /3/"<<endl;
    cout<<"$ 4. Diode pojemnosciowa z pokolorowanymi liniami: /4/"<<endl<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
}

void menu(bool condition)
{
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"$ Menu:"<<endl<<"$ 1. Dodaj nowy element /1/"<<endl<<"$ 2. Menu /2/"<<endl;
	if(condition)
	{
        cout<<"$ 7. Importuj z pliku txt/7/"<<endl;
		cout<<"$ 0. Wyjdz /0/"<<endl;
		cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
		return;
	}
	cout<<"$ 3. Wyswietl baze /3/"<<endl;
    cout<<"$ 4. Exportuj do SVG /4/"<<endl<<"$ 5. Usun element /5/"<<endl<<"$ 6. Eksportuj elementy do pliku txt /6/"<<endl;
    cout<<"$ 7. Importuj z pliku txt/7/"<<endl;
    cout<<"$ 8. Edytuj Element /8/"<<endl;
    cout<<"$ 0. Wyjdz /0/"<<endl;
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
}
