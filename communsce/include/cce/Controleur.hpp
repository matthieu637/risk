#ifndef CONTROLEUR_HPP
#define CONTROLEUR_HPP
#include "Modele.hpp"
#include "MoteurSFML.hpp"
#include "GUI.hpp"

namespace cce{

class Controleur
{

public:
    Controleur();
    void init(MoteurSFML* engine, GUI* gui);
    void appliquer_events(const Modele& m);
private:
  MoteurSFML* engine;
  GUI* gui;
};

}

#endif // CONTROLEUR_HPP
