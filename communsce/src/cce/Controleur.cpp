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
    Action right_press(sf::Mouse::Right, Action::PressOnce);
    Action right_release(sf::Mouse::Right, Action::ReleaseOnce);
    Action right_hold(sf::Mouse::Right, Action::Hold);
    Action mouse_move(sf::Event::MouseMoved);
    Action drag_right = mouse_move && right_hold;
    Action molette(sf::Event::MouseWheelMoved);
    Action rctrl_press(sf::Keyboard::RControl, Action::Hold);
    Action num0_press(sf::Keyboard::Num0, Action::Hold);
    Action rctrl_num0 = rctrl_press && num0_press;
    
    // Map
    map["quit"] = close;
    map["zoom"] = molette;
    map["reset_zoom"] = rctrl_num0;
    map["start_cam"] = right_press;
    map["stop_cam"] = right_release;
    map["move_camera"] = drag_right;

    //Binding map-fonctions
    system.connect("start_cam", std::bind(& Controleur::onStartCam, this, std::placeholders::_1));
    system.connect("stop_cam", std::bind(& Controleur::onStopCam, this, std::placeholders::_1));
    system.connect("move_camera", std::bind(& Controleur::onMoveCamera, this, std::placeholders::_1));
    system.connect("zoom", std::bind(& Controleur::onZoom, this, std::placeholders::_1));
    system.connect("reset_zoom", std::bind(& Controleur::onResetZoom, this, std::placeholders::_1));
}

void Controleur::appliquer_events()
{
    map.update();
    map.invokeCallbacks(system);
    
    if (map.isActive("quit"))
        engine->getFenetre()->close();
}

void Controleur::onStartCam(thor::ActionContext<string> context)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    clickX = mousePosition.x;
    clickY = mousePosition.y;
    int cameraX = engine->getView()->getCenter().x;
    int cameraY = engine->getView()->getCenter().y;
    m->setCamOrigine(cameraX, cameraY);
    moveCam = true;
}

void Controleur::onStopCam(thor::ActionContext<string> context)
{
    moveCam = false;
}

void Controleur::onMoveCamera(thor::ActionContext<string> context)
{
    if(!moveCam) //bug si exécuté avant le rightPress
      return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    int dx = clickX - mousePosition.x;
    int dy = clickY - mousePosition.y;
    int cameraX = engine->getView()->getCenter().x;
    int cameraY = engine->getView()->getCenter().y;
    int cameraL = engine->getView()->getSize().x;
    int cameraH = engine->getView()->getSize().y;
    m->moveView(dx, dy, cameraX, cameraY, cameraL, cameraH);
}

void Controleur::onZoom(thor::ActionContext<string> context)
{
    int ticks = context.event->mouseWheel.delta;
    m->zoom(ticks);
}

void Controleur::onResetZoom(thor::ActionContext<string> context)
{
    m->resetZoom();
}

}
