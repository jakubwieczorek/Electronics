/**
* \brief types witch I use in different files
*/

#include "Element.h"
#include <vector>
#include <map>

/// \brief new type pointer to function witch returns pointer to element
/// \details this type occured in container map when I keep number of ID and pointer to function which creating element
typedef Element * (*CreateElement)();
/**
* \brief container stores all elements.
*/
typedef std::vector <Element *> My_vector;
/**
* \brief container, in first component I store number of ID and the second pointer to function describing higher.
*/
typedef std::map<unsigned int, CreateElement> My_map;



