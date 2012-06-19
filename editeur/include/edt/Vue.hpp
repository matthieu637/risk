#ifndef VUEEDITEUR_HPP
#define VUEEDITEUR_HPP

///
///\file Vue.hpp
///\brief Gere l'affichage de SFML et de CEGUI
///\author matthieu, aymeric
///

#include <cce/Vue.hpp>
#include <string>
#include <list>

using std::string;
using std::list;

namespace cce {
  class MoteurSFML;
}

namespace edt {

class Modele;
class GUI;


class Vue : public cce::Vue
{

public:
    Vue(cce::MoteurSFML* engine, GUI* gui);
    ~Vue();
    void updateListRegions(list<string> noms);
    
    GUI* getGUI();
    
private:
};

}
#endif // VUE_HPP
