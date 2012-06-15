#ifndef VUEEDITEUR_HPP
#define VUEEDITEUR_HPP

///
///\file Vue.hpp
///\brief Gere l'affichage de SFML et de CEGUI
///\author matthieu, aymeric
///

#include <cce/Vue.hpp>

namespace edt {
  
class MoteurSFML;
class GUI;
class Modele;

class Vue : public cce::Vue
{

public:
    Vue();
    ~Vue();
    
private:
};

}
#endif // VUE_HPP
