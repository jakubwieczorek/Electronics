#include<iostream>
#include<math.h>
#include<fstream>
#include"../headers/SpinFtransistor.h"

using namespace std;

void SpinFtransistor::exp_to_txt(std::ofstream &file)
{
    file<<ID<<" ";
    file<<width<<" ";
    for(int i=0; i<3; i+=1)file<<Ftransistor::line_color[i]<<" ";
    for(int i=0; i<3; i+=1)file<<Ftransistor::interior_color[i]<<" ";
    file<<stroke_width<<" ";
    for(int i=0; i<2; i+=1)file<<local[i]<<" ";
    file<<name<<" ";
    file<<spin<<endl;
}

void SpinFtransistor::imp_from_txt(std::ifstream &file)
{
    file>>width;
    for(int i=0; i<3; i+=1)file>>line_color[i];
    for(int i=0; i<3; i+=1)file>>interior_color[i];
    file>>stroke_width;
    for(int i=0; i<2; i+=1)file>>local[i];
    file>>name;
    file>>spin;
}

SpinFtransistor::SpinFtransistor(unsigned short width, unsigned short line_color[], unsigned short interior_color[], unsigned short stroke_width, unsigned short local[], string name, unsigned short spin)
{
    Element::width=width;
    for(int i=0; i<3; i+=1)this->line_color[i]=line_color[i];
    for(int i=0; i<3; i+=1)Element::interior_color[i]=interior_color[i];
    Ftransistor::stroke_width=stroke_width;
    for(int i=0; i<2; i+=1)Element::local[i]=local[i];
    Ftransistor::name=name;
    this->spin=spin;
}

SpinFtransistor::SpinFtransistor()
{
    Element::width=100;
    for(int i=0; i<3; i+=1)Element::interior_color[i]=200;
    for(int i=0; i<2; i+=1)Element::local[i]=200;
    for(int i=0; i<3; i+=1)line_color[i]=100;
    stroke_width=5;
    name="SpinFtransistor";
    spin=0;
}

void SpinFtransistor::write_in_terminal()//wypisuje specyfikacje tego Ftransistoru w terminalu
{
    #define PRINT(x) cout<<#x<<": "<<x<<endl;
    PRINT(name);
    PRINT(width);
    PRINT(stroke_width);

    cout<<"line_color: rgb "<<line_color[0]<<" "<<line_color[1]<<" "<<line_color[2]<<endl;
    cout<<"interior_color: rgb "<<Element::interior_color[0]<<" "<<Element::interior_color[1]<<" "<<Element::interior_color[2]<<endl;
    cout<<"localization :"<<Element::local[0]<<" "<<Element::local[1]<<endl;
    PRINT(spin);
    #undef PRINT
}

void SpinFtransistor::exp_to_svg(ofstream &file)
{
//obrot
    file<<"<g transform=\"translate("<<local[0]<<","<<local[1]<<") rotate("<<spin<<" "<<local[0]<<" "<<local[1]<<")\">"<<endl;
//kolo
    file<<"<circle cx=\""<<Element::local[0]<<"\" cy=\""<<Element::local[1]<<"\" r=\""<<Element::width<<"\" style=\"stroke:rgb("<<line_color[0]<<",";
    file<<line_color[1]<<","<<line_color[2]<<"); "<<" stroke-width:"<<stroke_width;
    file<<"; fill:rgb("<<Element::interior_color[0]<<","<<Element::interior_color[1]<<","<<Element::interior_color[2]<<")\" />";
//linia w kole
    file<<endl<<" <line x1=\""<<(Element::local[0]-Element::width/4)<<"\" y1=\""<<(Element::local[1]-3*Element::width/4)<<"\" x2=\""<<(Element::local[0]-Element::width/4)<<"\" y2=\"";
    file<<(Element::local[1]+3*Element::width/4)<<"\""<<endl<<"style=\"stroke:rgb("<<line_color[0]<<","<<line_color[1]<<","<<line_color[2];
    file<<");"<<" stroke-width:"<<5*stroke_width<<"\" />"<<endl;
//polyline strzalka z lewej bez strzalki
    file<<"<polyline points=\"";int x1=(Element::local[0]-Element::width/4)-5*stroke_width; file<<x1<<",";
    int y1=Element::local[1]; file<<y1<<" "; int x2=x1-3*Element::width/4; file<<x2<<","; int y2=y1-3*Element::width/4;
    file<<y2<<" ";
    int ll=sqrt(pow(x1-x2,2) + pow(y1-y2,2)); //dlugosc lini od od punkt x do y
    int x3=x2;
    file<<x3<<","; int y3=y2+ll/4; file<<y3<<" "<<x3-ll/3<<","<<y3-ll/3<<"\""<<endl;
    file<<"style=\"fill:none; stroke:rgb("<<line_color[0]<<",";
    file<<line_color[1]<<","<<line_color[2]<<"); stroke-width:"<<stroke_width<<"\" />"<<endl;
//polyline strzalka z lewej
    file<<"<polyline points=\""<<x1-5*stroke_width/3<<","<<y1-5*stroke_width<<" "<<x1<<","<<y1<<" "<<x1-5*stroke_width<<",";
    file<<y1-5*stroke_width/3<<" "<<x1-5*stroke_width/3<<","<<y1-5*stroke_width<<endl;
    file<<"\" style=\"fill:rgb("<<line_color[0]<<","<<line_color[1]<<","<<line_color[2]<<"); stroke:rgb("<<line_color[0]<<",";
    file<<line_color[1]<<","<<line_color[2]<<"); stroke-width:"<<stroke_width<<"\" />"<<endl;
    file<<"</g>"<<endl;
}

unsigned int SpinFtransistor::ID=0;//to musi byc zainicjalizowane w innym pliku zrodlowym bo sie wysypie przez static
