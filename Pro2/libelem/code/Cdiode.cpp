#include"../headers/Cdiode.h"//tak mozna gdy headers jest na rownym poziomie co folder w ktorym jest plik zrodlowy u mnie code
#include<math.h>
#include<fstream>

using namespace std;

void Cdiode::exp_to_txt(std::ofstream &file)
{
    file<<ID<<" "<<Element::width<<" ";
    for(int i=0; i<3; i+=1)file<<Element::interior_color[i]<<" ";
    for(int i=0; i<2; i+=1)file<<Element::local[i]<<" ";
    file<<spin<<endl;
}

void Cdiode::imp_from_txt(std::ifstream &file)
{
    file>>Element::width;
    for(int i=0; i<3; i+=1)file>>Element::interior_color[i];
    for(int i=0; i<2; i+=1)file>>Element::local[i];
    file>>spin;
}

Cdiode::Cdiode()
{
    Element::width=100;
    for(int i=0; i<3; i+=1)Element::interior_color[i]=100;
    for(int i=0; i<2; i+=1)Element::local[i]=100;
    this->spin=0;
}

Cdiode::Cdiode(unsigned short width, unsigned short interior_color[], unsigned short local[], unsigned short spin)
{
    Element::width=width;
	for(int i=0; i<3; i+=1)Element::interior_color[i]=interior_color[i];
	for(int i=0; i<2; i+=1)Element::local[i]=local[i];
	this->spin=spin;
} //Element - konstruktor
void Cdiode::write_in_terminal()
{
    #define PRINT(x) cout<<#x<<": "<<x<<endl;
    PRINT(width);
	cout<<"interior_color: rgb "<<Element::interior_color[0]<<" "<<Element::interior_color[1]<<" "<<Element::interior_color[2]<<endl;
    cout<<"localization :"<<Element::local[0]<<" "<<Element::local[1]<<endl;
	PRINT(spin);
    cout<<endl;
	#undef PRINT
}

void Cdiode::exp_to_svg(ofstream &file)//eksportuje element do pliku svg
{
	/* zmienne pomocnicze ulatwiajace opis obrazka (bez uwzgledniania obrotu i polozenia poczatkowego),
       stosunki dlugosci poszczegolnych czesci symbolu diody ustalone arbitralnie: */

    float koniec_przewodu1 = width/4.0; //wspolrzedna x konca przewodu "+"
    float koniec_trojkata = width*5.0/8.0; //wsp. x trojkatnej czesci symbolu diody
    float poczatek_przewodu2 = width*3.0/4.0; //wsp. x poczatku przeowodu "-" (zaczyna sie on tam, gdzie konczy sie czesc symbolu diody ("pojemnosc") - pionowe linie)
    float wysokosc_symbolu = width/4.0; //wysokosc, tzn. wspolrzedna y gornego kranca obrazka


	/* zapisanie informacji o obrazku w strumieniu wyjsciowym: */

    //ciag dalszy << - ponizej
	//obrot i translacja (zgodnie z podanymi wspolrzednymi poczatkowymi)- dotyczy wszystkiego, co jest miedzy <g> a </g>:
    file<<"\n  <g transform=\"translate("<<Element::local[0]<<","<<Element::local[1]<<") rotate("<<spin<<")\""

	//kolor i grubosc wszystkich linii; + jednoargumentowy - zeby unsigned char zapisac jako liczbe:
	" style=\"stroke:rgb("<<Element::interior_color[0]<<","<<Element::interior_color[1]<<","<<Element::interior_color[2]<<"); stroke-width: 2\">"

	//przewod "+":
	"\n    <line x1=\"0\" y1=\"0\" x2=\""<<koniec_przewodu1<<"\" y2=\"0\"/>"

	 //wielokat - trojkat symbolizujacy diode:
	 "\n    <polygon points=\""<<koniec_przewodu1<<","<<-wysokosc_symbolu<<" "<<koniec_przewodu1<<","<<wysokosc_symbolu<<" "<<koniec_trojkata<<","<<0<<"\""

	 //styl wielokata nieuwzgledniony w <g>; grubosc linii:0 - zeby trojkat konczyl sie dokladnie tam, gdzie zaczynaja sie pionowe linie
	 " style=\"fill:rgb("<<Element::interior_color[0]<<","<<Element::interior_color[1]<<","<<Element::interior_color[2]<<"); stroke-width: 0\"/>"

	 //pierwsza pionowa linia ("pojemnosc"):
	"\n    <line x1=\""<<koniec_trojkata<<"\" y1=\""<<-wysokosc_symbolu<<"\" x2=\""<<koniec_trojkata<<"\" y2=\""<<wysokosc_symbolu<<"\"/>"

	 //druga pionowa linia ("pojemnosc"):
	"\n    <line x1=\""<<poczatek_przewodu2<<"\" y1=\""<<-wysokosc_symbolu<<"\" x2=\""<<poczatek_przewodu2<<"\" y2=\""<<wysokosc_symbolu<<"\"/>"

	 //przewod "-":
    "\n    <line x1=\""<<poczatek_przewodu2<<"\" y1=\"0\" x2=\""<<width<<"\" y2=\"0\"/>"

	 "\n  </g>\n\n"; //nie ma </svg> po kazdym elemencie (jest dopiero na koncu dokumentu), bo poszczegolne elementy beda zagniezdzone
}

unsigned int Cdiode::ID=0;
