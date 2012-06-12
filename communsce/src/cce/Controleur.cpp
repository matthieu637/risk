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
    Action right_hold(sf::Mouse::Right, Action::Hold);
    Action mouse_move(sf::Event::MouseMoved);
    Action drag_right = mouse_move && right_hold;
    
    // Map
    map["quit"] = close;
    map["move_camera"] = drag_right;

    system.connect("move_camera", std::bind(& Controleur::onMoveCamera, this, std::placeholders::_1));
    
}

void Controleur::appliquer_events(){    
    map.update();
    map.invokeCallbacks(system);
    
    if (map.isActive("quit"))
        engine->getFenetre()->close();
}



void Controleur::onMoveCamera(thor::ActionContext<string> context)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    int dx = mousePosition.x - clickX;
    int dy = mousePosition.y - clickY;
    int cameraX = engine->getView()->getCenter().x;
    int cameraY = engine->getView()->getCenter().y;
    int cameraL = engine->getView()->getSize().x;
    int cameraH = engine->getView()->getSize().y;
    m->moveView(dx, dy, cameraX, cameraY, cameraL, cameraH);
}

}
