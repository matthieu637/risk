#ifndef CONTROLEUR_HPP
#define CONTROLEUR_HPP
#include "Modele.hpp"
#include "MoteurSFML.hpp"
#include "GUI.hpp"

///
///\file Controleur.hpp
///\brief Controleur du MVC principale, il sert à dispatcher et traiter les évènements
///\author matthieu
///

namespace cce{

class Controleur
{

public:
    Controleur();
///
///\brief Simple setter, engine et gui doivent être les mêmes que celui de la vue
///
    void init(MoteurSFML* engine, GUI* gui);
    
///
///\brief Récupère les events de SFML et les applique au modèle ou à la GUI
///
    void appliquer_events(const Modele& m);
private:
  MoteurSFML* engine;
  GUI* gui;
};

}

#endif // CONTROLEUR_HPP
