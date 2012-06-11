#ifndef CONTROLEUR_HPP
#define CONTROLEUR_HPP

///
///\file Controleur.hpp
///\brief Controleur du MVC principale, il sert à dispatcher et traiter les évènements
///\author matthieu
///

namespace cce{

class Modele;
class MoteurSFML;
class GUI;
  
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
    void appliquer_events(Modele& m);
  
private:
    MoteurSFML* engine;
    GUI* gui;
    bool rightPressed;
    int curseurX, curseurY;
};

}

#endif // CONTROLEUR_HPP
