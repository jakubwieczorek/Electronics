/**
* \brief class LCCdiode inherit from Cdiode
* \details   contain mathods witch allow generate svg code. It's capacity diode with colored lines
* and this simbol is generated.
* \author Jakub Wieczorek
*/

#ifndef LCCdiode_H
#define LCCdiode_H
#include"Cdiode.h"


class LCCdiode : public Cdiode{

protected:
    /// \brief line color
    unsigned short line_color[3];

public:
    static unsigned ID;
    /**
    * \brief default constructor
    * \details
    * width = 100;
    * all interior_color = 100;
    * all line_color = 50
    * all local = 100;
    * spin = 0;
    */
    LCCdiode();
    /// \brief constructor
    LCCdiode(unsigned short width, unsigned short interior_color[], unsigned short local[], unsigned short spin, unsigned short line_color[]);//konstrukto

    /**
    * \brief static function returning pointer to object LCCdiode.
    * \details Given to object type Factory. It's explaining why this function is static.
    */
    static Element *  CreateLCCdiode(){return new LCCdiode();}
    /// \brief setter line color
    void set_line_color(unsigned short line_color[]){for(int i=0; i<3; i++)this->line_color[i]=line_color[i];}
    /**
    * \brief show ID class LCCdiode. Returns ID.
    *
    */
    virtual unsigned int show_ID(){return ID;}
    /**
    * \brief It's describing specification of object type LCCdiode in terminal.
    * \details Come from class of Element
    */
    virtual void write_in_terminal();
    /** \brief Exports LCCdiode to svg.
     * \param file to this file will be exported code svg describing LCCdiode.
     * \attention file should be opened and extension should be .svg. This method don't close file.
     */
    virtual void exp_to_svg(std::ofstream &file);
    /** \brief Exports specification of LCCdiode to file.
     * \param file to this file will be exported all information of LCCdiode.
     * \attention file should be open, prefered extension is .txt. This method don't close file.
     */
    virtual void exp_to_txt(std::ofstream &file);
    /** \brief Imports specification of LCCdiode from file.
     * \param file from this will be imported all information of LCCdiode.
     * \attention file should be open. This method don't close file. */
    virtual void imp_from_txt(std::ifstream &file);
};
#endif

