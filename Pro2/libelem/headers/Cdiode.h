/**
* \brief class Cdiodeinherit from Element
* \details   contain mathods witch allow generate svg code. It's capacity diode and this simbol is generated.
* \author    Tomasz Nowak
*/
#ifndef Cdiode_H
#define Cdiode_H
#include"Element.h"

class Cdiode: public Element {

protected:
    ///spin involved amount of degrees. How much capacity diode is rotated.
	unsigned short spin;

public:
    /// This is ID of this class. You can see field is static so every object of this type has the same ID.
    /// This is given by method of Factory class.
    static unsigned ID;

    /**
    * \brief default constructor
    * \details
    * width = 100;
    * all interior_color = 100;
    * all local = 100;
    * spin = 0;F
    */
    Cdiode();
    ///constructor
    Cdiode(unsigned short width, unsigned short interior_color[], unsigned short local[], unsigned short spin);//konstrukto
    /// \brief setter for spin
    void set_spin(unsigned short spin){this->spin=spin;}

    /**
    * \brief static function returning pointer to object Cdiode.
    * \details Given to object type Factory. It's explaining why this function is static.
    */
    static Element *  CreateCdiode(){return new Cdiode();}

    /**
    * \brief show ID class Cdiode. Returns ID.
    *
    */
    virtual unsigned int show_ID(){return ID;}
    /**
    * \brief It's describing specification of object type Cdiode in terminal.
    * \details Come from class of Element
    */
    virtual void write_in_terminal();
    /** \brief Exports Cdiodeto svg.
     * \param file to this file will be exported code svg describing Cdiode.
     * \attention file should be opened and extension should be .svg. This method don't close file.
     */
    virtual void exp_to_svg(std::ofstream &file);
    /** \brief Exports specification of Cdiodeto file.
     * \param file to this file will be exported all information of Cdiode.
     * \attention file should be open, prefered extension is .txt. This method don't close file.
     */
    virtual void exp_to_txt(std::ofstream &file);
    /** \brief Imports specification of Cdiodefrom file.
     * \param file from this will be imported all information of Cdiode.
     * \attention file should be open. This method don't close file. */
    virtual void imp_from_txt(std::ifstream &file);
};
#endif
