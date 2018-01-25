class Element {
 unsigned short width;//szerokosc/wielkosc
 unsigned short line_color[3];
 unsigned short interior_color[3];
 unsigned short stroke_weight;
 unsigned short local[2];
 //char name[20];
 std::string name;
public:
 Element(unsigned short, unsigned short[], unsigned short[], unsigned short, unsigned short[], std::string);//konstruktor
 void draw(std::ofstream &file);//eksportuje elemnt do pliku svg
 void write();//wypisuje elemnt w terminalu
};

