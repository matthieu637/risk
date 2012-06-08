#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

///
///\file StringUtils.hpp
///\brief Quelques méthodes de manipulation des strings
///\author matthieu
///
///

#include <string>

using namespace std;

namespace bib {

///
///\brief Supprime tous les chiffres d'une chaîne de caractères
///\param s : chaîne de départ
///\return la chaîne sans chiffre
///
  
string rmNumber(const string s);

///
///\brief Supprime tous les premiers chiffres d'une chaîne de caractères
///\param s : chaîne de départ
///\return la chaîne sans ses premiers chiffre
///

string rmFirstNumber(const string s);

}


#endif
