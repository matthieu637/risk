#include "cce/Controleur.hpp"
#include "cce/MoteurSFML.hpp"
#include <cce/GUI.hpp>
#include <cce/CppScriptModule.hpp>
#include <cce/Console.hpp>
#include <SFML/Window/Event.hpp>
#include <Thor/Events/Action.hpp>
#include <Thor/Events/EventSystem.hpp>


using thor::Action;

namespace cce {

Controleur::Controleur(MoteurSFML* engine, GUI* gui) : map(*(engine->getFenetre()))
{
    this->engine = engine;
    this->gui = gui;

    moduleGUI = new CppScriptModule;

    // Evenements Thor
    Action close(sf::Event::Closed);

    // Map
    map["quit"] = close;
}

void Controleur::appliquer_events()
{
    sf::Event e;

    gui->tocHorloge();
    map.clearEvents();

    while(engine->getFenetre()->pollEvent(e)) {
        // décommenter pour ignorer les events utilisé par CEGUI
        if(gui->captureEvent(e))
            continue;

        map.pushEvent(e);
    }

    map.invokeCallbacks(system);

    if (map.isActive("quit"))
        gui->getConsole()->afficherCommande("/quit");
}

bool Controleur::isRunning()
{
    return engine->getFenetre()->isOpen();
}

}
