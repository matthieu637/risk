#include "cce/Controleur.hpp"
#include "cce/MoteurSFML.hpp"
#include <SFML/Window/Event.hpp>

namespace cce{

Controleur::Controleur()
{

}

void Controleur::init(MoteurSFML* engine, GUI* gui)
{
    this->engine = engine;
    this->gui = gui;
}

void Controleur::appliquer_events(Modele& m){
    (void)m;
  
    sf::Event event;
    while (engine->getFenetre()->pollEvent(event))
    {
	if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
	    rightPressed = true;
	    curseurX = event.mouseButton.x;
	    curseurY = event.mouseButton.y;
	}

	if(rightPressed && event.type == sf::Event::MouseMoved) {
	    m.moveView(curseurX - event.mouseMove.x, curseurY - event.mouseMove.y);
	    curseurX = event.mouseMove.x;
	    curseurY = event.mouseMove.y;
	}

	if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
	    rightPressed = false;
	}
	
	if (event.type == sf::Event::Closed) {
	    engine->getFenetre()->close();
        }
    }
}

}
