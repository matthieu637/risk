#include "edt/Controleur.hpp"
#include "edt/Modele.hpp"
#include "edt/GUI.hpp"
#include "cce/MoteurSFML.hpp"
#include <SFML/Window/Event.hpp>
#include <Thor/Events/Action.hpp>
#include <Thor/Events/EventSystem.hpp>

using thor::Action;

namespace edt{
  
Controleur::Controleur(cce::MoteurSFML* engine, Modele* m, GUI* gui) : cce::Controleur(engine, gui)
{
    this->m = m;
    tile = true;
  
    // Evenements Thor
    Action close(sf::Event::Closed);
    Action right_press(sf::Mouse::Right, Action::PressOnce);
    Action right_release(sf::Mouse::Right, Action::ReleaseOnce);
    Action right_hold(sf::Mouse::Right, Action::Hold);
    Action left_release(sf::Mouse::Left, Action::ReleaseOnce);
    Action left_hold(sf::Mouse::Left, Action::Hold);
    Action mouse_move(sf::Event::MouseMoved);
    Action molette(sf::Event::MouseWheelMoved);
    Action rctrl_press(sf::Keyboard::RControl, Action::Hold);
    Action num0_press(sf::Keyboard::Num0, Action::Hold);
    Action rctrl_num0 = rctrl_press && num0_press;
    Action drag_right = mouse_move && right_hold;
    Action drag_left = mouse_move && left_hold;
    
    // Map
    map["quit"] = close;
    map["zoom"] = molette;
    map["reset_zoom"] = rctrl_num0;
    map["start_cam"] = right_press;
    map["stop_cam"] = right_release;
    map["move_camera"] = drag_right;
    map["placer_objet"] = drag_left || left_release;

    //Binding map-fonctions
    system.connect("start_cam", std::bind(& Controleur::onStartCam, this, std::placeholders::_1));
    system.connect("stop_cam", std::bind(& Controleur::onStopCam, this, std::placeholders::_1));
    system.connect("move_camera", std::bind(& Controleur::onMoveCamera, this, std::placeholders::_1));
    system.connect("zoom", std::bind(& Controleur::onZoom, this, std::placeholders::_1));
    system.connect("reset_zoom", std::bind(& Controleur::onResetZoom, this, std::placeholders::_1));
    system.connect("placer_objet", std::bind(& Controleur::onPlaceObject, this, std::placeholders::_1));
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
    (void) context;
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
    m->moveView(dx, dy, cameraX, cameraY);
}

void Controleur::onZoom(thor::ActionContext<string> context)
{
    int ticks = context.event->mouseWheel.delta;
    m->zoom(ticks);
}

void Controleur::onResetZoom(thor::ActionContext<string> context)
{
    (void) context;
    m->resetZoom();
}

void Controleur::onPlaceObject(thor::ActionContext<string> context)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    int x_view = engine->getView()->getCenter().x - engine->getView()->getSize().x/2;
    int y_view = engine->getView()->getCenter().y - engine->getView()->getSize().y/2;
    int x_absolu = x_view + mousePosition.x;
    int y_absolu = y_view + mousePosition.y;
    if(tile)
      m->placeTile(x_absolu, y_absolu);
    else if(decor)
      m->placeDecor(x_absolu, y_absolu);
}

}
