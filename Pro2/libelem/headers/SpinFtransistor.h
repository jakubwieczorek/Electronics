/**
* \brief class spinSpinFtransistor inherit from SpinFtransistor
* \details   contain mathods witch allow generate svg code. It's phototransistor witch can be
* rotated and this simbol is generated.
* \author    Jakub Wieczorek
*/

#ifndef SPINSpinFtransistor_H
#define SPINSpinFtransistor_H
#include"Ftransistor.h"

class SpinFtransistor : public Ftransistor{
protected:
    ///spin involved amount of degrees. How much element is rotated.
    unsigned short spin;
public:
    /// \brief setter to spin
    void set_spin(unsigned short spin){this->spin=spin;}
    /// This is ID of this class. You can see field is static so every object of this type has the same ID.
    /// This is given by method of Factory class.
    static unsigned int ID;
    ///\brief constructor
    SpinFtransistor(unsigned short width, unsigned short line_color[], unsigned short interior_color[], unsigned short stroke_width, unsigned short local[], std::string name, unsigned short spin);//konstruktor
    /**
    * \brief default constructor
    * \details
    * width = 100
    * all interior_color = 200
    * all local = 200
    * all line color = 100
    * name = SpinFtransistor
    * stroke_width = 5
    * spin = 0
    */
    SpinFtransistor();
    /**
    * \brief static function returning pointer to object of SpinFtransistor ID.
    * \details Given to object type Factory. It's explaining why this function is static.
    */
    static Element *  CreateSpinFtransistor(){return new SpinFtransistor();}
    /**
    * \brief show ID class of spinSpinFtransistor. Returns ID.
    *
    */
    virtual unsigned int show_ID(){return ID;}
    /** \brief Exports spinSpinFtransistor to svg.
     * \param file to this file will be exported code svg describing ftrasistor.
     * \attention file should be opened and extension should be .svg. This method don't close file.
     */
    virtual void exp_to_svg(std::ofstream &file);
    /**
    * \brief It's describing specification of object type SpinFtransistor in terminal.
    * \details Come from class of Element
    */
    virtual void write_in_terminal();
    /** \brief Exports specification of SpinFtransistor to file.
     * \param file to this file will be exported all information of SpinFtransistor.
     * \attention file should be open, prefered extension is .txt. This method don't close file.
     */
    virtual void exp_to_txt(std::ofstream &file);
    /** \brief Imports specification of SpinFtransistor from file.
     * \param file from this will be imported all information of SpinFtransistor.
     * \attention file should be open. This method don't close file. */
    virtual void imp_from_txt(std::ifstream &file);
};
#endif
