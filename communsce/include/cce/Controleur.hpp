#ifndef CONTROLEUR_HPP
#define CONTROLEUR_HPP
#include <string.h>
#include <Thor/Events/ActionMap.hpp>
#include <Thor/Events/EventSystem.hpp>

using std::string;

///
///\file Controleur.hpp
///\brief Controleur du MVC principale, il sert à dispatcher et traiter les évènements
///\author matthieu, aymeric
///

namespace cce{

class MoteurSFML;
class GUI;
  
class Controleur
{

public:
///
///\brief Simple setter, engine et gui doivent être les mêmes que celui de la vue
///
    Controleur(MoteurSFML* engine, GUI* gui);
    
///
///\brief Récupère les events de SFML et les applique au modèle ou à la GUI
///
    void appliquer_events();
    
    bool isRunning();
  
protected:
    MoteurSFML* engine;
    GUI* gui;
    thor::ActionMap<std::string> map;
    thor::ActionMap<string>::CallbackSystem system;
};

}

#endif // CONTROLEUR_HPP
