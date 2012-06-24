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

namespace cli {

class Modele;
class GUI;


class Vue : public cce::Vue
{

public:
    Vue(cce::MoteurSFML* engine, GUI* gui);
    ~Vue();

    void updateCameraPosition(int x, int y);
    
    void updateCameraZoom(float factor);
    
    void updateSize(int width, int height);
    
    GUI* getGUI();

    
private:
};

}
#endif // VUE_HPP

