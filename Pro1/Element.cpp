#include"Dokument.h"
#include<iostream>
#include<math.h>

using namespace std;

Element::Element(unsigned short width, unsigned short line_color[], unsigned short interior_color[], unsigned short stroke_weight, unsigned short local[], string name)
{
	this->width=width;
	for(int i=0; i<3; i+=1)this->line_color[i]=line_color[i];
	for(int i=0; i<3; i+=1)this->interior_color[i]=interior_color[i];
	this->stroke_weight=stroke_weight;
	for(int i=0; i<2; i+=1)this->local[i]=local[i];
	//strcpy(this->name, name);
	this->name=name;

}//konstruktor Element

void Element::write()//wypisuje specyfikacje tego elementu w terminalu
{
	#define PRINT(x) cout<<#x<<": "<<x<<endl;
	PRINT(name);
	PRINT(width);
	PRINT(stroke_weight);

	cout<<"line_color: rgb "<<line_color[0]<<" "<<line_color[1]<<" "<<line_color[2]<<endl;
	cout<<"interior_color: rgb "<<interior_color[0]<<" "<<interior_color[1]<<" "<<interior_color[2]<<endl;
	cout<<"localization :"<<local[0]<<" "<<local[1]<<endl<<endl;
	#undef PRINT
}

void Element::draw(std::ofstream &file)
{
//kolo
	file<<"<circle cx=\""<<local[0]<<"\" cy=\""<<local[1]<<"\" r=\""<<width<<"\" style=\"stroke:rgb("<<line_color[0]<<",";
	file<<line_color[1]<<","<<line_color[2]<<"); "<<" stroke-width:"<<stroke_weight;
   	file<<"; fill:rgb("<<interior_color[0]<<","<<interior_color[1]<<","<<interior_color[2]<<")\" />";
//linia w kole
 	file<<endl<<" <line x1=\""<<(local[0]-width/4)<<"\" y1=\""<<(local[1]-3*width/4)<<"\" x2=\""<<(local[0]-width/4)<<"\" y2=\"";
	file<<(local[1]+3*width/4)<<"\""<<endl<<"style=\"stroke:rgb("<<line_color[0]<<","<<line_color[1]<<","<<line_color[2];
	file<<");"<<" stroke-width:"<<5*stroke_weight<<"\" />"<<endl;
//polyline strzalka z lewej bez strzalki
	file<<"<polyline points=\"";int x1=(local[0]-width/4)-5*stroke_weight; file<<x1<<",";
	int y1=local[1]; file<<y1<<" "; int x2=x1-3*width/4; file<<x2<<","; int y2=y1-3*width/4;
	file<<y2<<" ";
	int ll=sqrt(pow(x1-x2,2) + pow(y1-y2,2)); //dlugosc lini od od punkt x do y
	int x3=x2;
	file<<x3<<","; int y3=y2+ll/4; file<<y3<<" "<<x3-ll/3<<","<<y3-ll/3<<"\""<<endl;
 	file<<"style=\"fill:none; stroke:rgb("<<line_color[0]<<",";
	file<<line_color[1]<<","<<line_color[2]<<"); stroke-width:"<<stroke_weight<<"\" />"<<endl;
//polyline strzalka z lewej
	file<<"<polyline points=\""<<x1-5*stroke_weight/3<<","<<y1-5*stroke_weight<<" "<<x1<<","<<y1<<" "<<x1-5*stroke_weight<<",";
	file<<y1-5*stroke_weight/3<<" "<<x1-5*stroke_weight/3<<","<<y1-5*stroke_weight<<endl;
 	file<<"\" style=\"fill:rgb("<<line_color[0]<<","<<line_color[1]<<","<<line_color[2]<<"); stroke:rgb("<<line_color[0]<<",";
	file<<line_color[1]<<","<<line_color[2]<<"); stroke-width:"<<stroke_weight<<"\" />"<<endl;

}

