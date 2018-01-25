/**
* \brief class container to operate and storing elements
* \author    Jakub Wieczorek
*/
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include<string>
#include<fstream>
#include"SpinFtransistor.h"
#include"LCCdiode.h"
#include<vector>
#include"Factory.h"

class Dokument {
public:
/**
* \brief in this container I keep all elements
*/
 std::vector<Element *>container;
 ///\brief iterator to container
 std::vector<Element *>::iterator it_el;
 /**
 * \brief operator to adding elements
 * \details example:
 * we have container name BOX and element diode:
 * BOX=BOX+diode;
 *
 */
 Dokument operator+(Element *el_to_add);
 /**
 * \brief operator to deleting elements
 * \details example:
 * \param pointer to element to delete
 * we have container name BOX and 4 elements, we want delete second so:
 * BOX=BOX-2;
 * in the second field now is third
 * \param number of element to delete
 */
 Dokument operator-(int i);
 /**
 * \brief writing specifications of all elements in container
 */
 void write_in_terminal();
 /**
 * \brief operator to export all elements to svg.
 * \param name_file name of file when elements should be export
 * \return true when operation ends in success false when some errors
 * \attention name_file should be ended with .svg extension. But not demanding.
 * \details example:
 * std:: string name="file";
 * contener>>file;
 * Function is throwing examples of type bool when error will apear during opening file.
 */
 bool operator>>(std::string name_file) throw(bool&);
 //void mod(int which, int whichfun);//pierwszy ktory element zmienic, drugi ktora skladowa
 /**
 * \brief export all elements to txt.
 * \param name_file name of file when elements should be export
 * \return true when operation ends in success false when some errors
 * \attention name_file should be ended with .txt extension. But not demanding.
 * \details example:
 * std:: string name="file";
 * contener>>file;
 * Function is throwing examples of type bool when error will apear during opening file.
 */
 bool exp_to_txt(std::string &name_file) throw(bool&);
 /**
 * \brief import all elements to txt.
 * \param name_file name of file from elements should be imported
 * \param f is referention to object of Factory, whose gives ID of all elements
 * \return true when operation ends in success
 * \attention name_file should be ended with .txt extension. But not demanding
 * \details example:
 * std:: string name="file";
 * contener>>file;
 * Function is throwing examples of type bool when error will apear during opening file.
 */
 bool imp_from_txt(std::string &name_file, Factory &f) throw(bool&);
};

#endif
