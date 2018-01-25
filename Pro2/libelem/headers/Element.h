/**
* \brief class Element
* The highest class in hierarchy. The parent of classes Ftransistor and cdiode.
* \details   Includes clear virtual methodes.
* \author    Jakub Wieczorek
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include<iostream>
#include<fstream>

class Element {
protected:
 /// the size of Element
 unsigned short width;
 /// the interior color in rgb
 unsigned short interior_color[3];
 /** the localization of Element. First component is distance from (0.0) point in x shaft
  and the second is respectively distance from y shaft.*/
 unsigned short local[2];
public:
 /** \brief Setter to width field */
 void set_width(unsigned short width){this->width=width;}
 /** \brief Setter to interior_color fields*/
 void set_interior_color(unsigned short interior_color[]){for(int i=0; i<3; i++)this->interior_color[i]=interior_color[i];}
 /** \brief Setter to local field*/
 void set_local(unsigned short local[]){for(int i=0; i<2; i++)this->local[i]=local[i];}


 /** \brief Reurnes ID of element. Defined in each child class. */
 virtual unsigned int show_ID() = 0;
 /** \brief Exports element to svg. Defined in each child class.
  * \param file to this file will be exported code svg describing element.
  * \attention file should be open and extension should be .svg. This method don't close file.
  */
 virtual void exp_to_svg(std::ofstream &file) = 0;
 /** \brief Show specification of this element in terminal. Defined in each child class. */
 virtual void write_in_terminal() = 0;
 /** \brief Exports specification of element to file. Defined in each child class.
  * \param file to this file will be exported all information of element.
  * \attention file should be open, prefered extension is .txt. This method don't close file.
  */
 virtual void exp_to_txt(std::ofstream &file) = 0;

 /** \brief Imports specification of element from file. Defined in each child class.
  * \param file from this will be imported all information of element.
  * \attention file should be open. This method don't close file. */
 virtual void imp_from_txt(std::ifstream &file) = 0;
};
#endif
