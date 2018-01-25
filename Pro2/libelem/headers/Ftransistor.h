/**
* \brief class Ftransistor inherit from Element
* \details   contain mathods witch allow generate svg code. It's phototransistor and this simbol is generated.
* \author    Jakub Wieczorek
*/

#ifndef Ftransistor_H
#define Ftransistor_H
#include"Element.h"

class Ftransistor : public Element{

protected:
 ///the line color in rgb.
 unsigned short line_color[3];
 ///stroke width
 unsigned short stroke_width;
 ///name of particular Ftransistor
 std::string name;
public:
 /// This is ID of this class. You can see field is static so every object of this type has the same ID.
 /// This is given by method of Factory class.
 static unsigned int ID;
 ///constructor
 Ftransistor(unsigned short width, unsigned short line_color[], unsigned short interior_color[], unsigned short stroke_width, unsigned short local[], std::string name);//konstruktor
 /**
 * \brief default constructor
 * \details
 * width = 100
 * all interior_color = 200
 * all local = 200
 * all line color = 100
 * name = Ftransistor
 * stroke_width = 5
 */
 Ftransistor();
 /// \brief setter to line_collor
 void set_line_color(unsigned short line_color[]){for(int i=0; i<3; i++)this->line_color[i]=line_color[i];}
 /// \brief setter to stroke_width
 void set_stroke_width(unsigned short stroke_width){this->stroke_width=stroke_width;}
 /// \brief setter to name
 void set_name(std::string name){this->name=name;}
 /**
 * \brief static function returning pointer to object of Ftransistor type.
 * \details Given to object type Factory. It's explaining why this function is static.
 */
 static Element *  CreateFtransistor(){return new Ftransistor();}

 /**
 * \brief show ID class of Ftransistor. Returns ID.
 *
 */
 virtual unsigned int show_ID(){return ID;}
 /**
 * \brief It's describing specification of object type Ftransistor in terminal.
 * \details Come from class of Element
 */
 virtual void write_in_terminal();
 /** \brief Exports Ftransistor to svg.
  * \param file to this file will be exported code svg describing ftrasistor.
  * \attention file should be opened and extension should be .svg. This method don't close file.
  */
 virtual void exp_to_svg(std::ofstream &file);
 /** \brief Exports specification of Ftransistor to file.
  * \param file to this file will be exported all information of Ftransistor.
  * \attention file should be open, prefered extension is .txt. This method don't close file.
  */
 virtual void exp_to_txt(std::ofstream &file);
 /** \brief Imports specification of Ftransistor from file.
  * \param file from this will be imported all information of Ftransistor.
  * \attention file should be open. This method don't close file. */
 virtual void imp_from_txt(std::ifstream &file);
};
#endif
