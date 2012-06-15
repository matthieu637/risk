#include "cce/Controleur.hpp"
#include "cce/MoteurSFML.hpp"
#include <SFML/Window/Event.hpp>
#include <Thor/Events/Action.hpp>
#include <Thor/Events/EventSystem.hpp>


using thor::Action;

namespace cce{
  
Controleur::Controleur(MoteurSFML* engine, Modele* m, GUI* gui) : map(*(engine->getFenetre()))
{
    this->engine = engine;
    this->m = m;
    this->gui = gui;
    
    // Evenements Thor
    Action close(sf::Event::Closed);
    
    // Map
    map["quit"] = close;
}

void Controleur::appliquer_events()
{
    map.update();
    map.invokeCallbacks(system);
    
    if (map.isActive("quit"))
        engine->getFenetre()->close();
}

}
