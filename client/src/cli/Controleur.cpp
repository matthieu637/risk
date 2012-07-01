#include "cli/Controleur.hpp"
#include "cli/Modele.hpp"
#include "cli/GUI.hpp"
#include "cce/MoteurSFML.hpp"
#include <cce/CppScriptModule.hpp>
#include <cce/Console.hpp>
#include <SFML/Window/Event.hpp>
#include <CEGUI/elements/CEGUIScrollbar.h>
#include <CEGUI/elements/CEGUIFrameWindow.h>
#include <CEGUI/elements/CEGUICheckbox.h>
#include <CEGUI/elements/CEGUIMenuItem.h>
#include <CEGUI/elements/CEGUIPopupMenu.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <Thor/Events/Action.hpp>
#include <Thor/Events/EventSystem.hpp>
#include "bib/Logger.hpp"

using thor::Action;

namespace cli {

Controleur::Controleur(cce::MoteurSFML * engine, Modele * m, GUI * gui):cce::Controleur(engine, gui) {
    this->m = m;

    // Evenements Thor
    Action close(sf::Event::Closed);
    Action resize(sf::Event::Resized);
    Action right_press(sf::Mouse::Right, Action::PressOnce);
    Action right_release(sf::Mouse::Right, Action::ReleaseOnce);
    Action left_press(sf::Mouse::Left, Action::PressOnce);
    Action left_release(sf::Mouse::Left, Action::ReleaseOnce);
    Action left_hold(sf::Mouse::Left, Action::Hold);
    Action wheel_hold(sf::Mouse::Middle, Action::Hold);
    Action wheel_press(sf::Mouse::Middle, Action::PressOnce);
    Action wheel_release(sf::Mouse::Middle, Action::ReleaseOnce);
    Action molette(sf::Event::MouseWheelMoved);
    Action mouse_move(sf::Event::MouseMoved);
    Action drag_wheel = mouse_move && wheel_hold;
    Action drag_left = mouse_move && left_hold;

    Action space_press(sf::Keyboard::Space, Action::ReleaseOnce);
    Action t_press(sf::Keyboard::T, Action::ReleaseOnce);
    Action d_press(sf::Keyboard::D, Action::ReleaseOnce);
    Action rctrl_press(sf::Keyboard::RControl, Action::Hold);
    Action num0_press(sf::Keyboard::Num0, Action::Hold);
    Action rctrl_num0 = rctrl_press && num0_press;

    // Map
    map["quit"] = close;
    map["zoom"] = molette;
    map["resize"] = resize;
    map["reset_zoom"] = rctrl_num0;
    map["start_cam"] = wheel_press;
    map["stop_cam"] = wheel_release;
    map["move_camera"] = drag_wheel;
    map["move_unit"] = right_press;
    map["selectionOn"] = left_press;
    map["selectionMove"] = drag_left;
    map["selectionOff"] = left_release;
    
    //Binding map-fonctions
    system.connect("start_cam", BIND(&Controleur::onStartCam));
    system.connect("stop_cam", BIND(&Controleur::onStopCam));
    system.connect("move_camera", BIND(&Controleur::onMoveCamera));
    system.connect("zoom", BIND(&Controleur::onZoom));
    system.connect("reset_zoom", BIND(&Controleur::onResetZoom));
    system.connect("resize", BIND(&Controleur::onWindowResized));
    system.connect("move_unit", BIND(&Controleur::onMoveUnit));
    system.connect("selectionOn", BIND(&Controleur::selectionOn));
    system.connect("selectionOff", BIND(&Controleur::selectionOff));
    system.connect("selectionMove", BIND(&Controleur::selectionMove));

    //Binding fonctions CEGUI
    
    gui->setScriptModule(moduleGUI);
}
void Controleur::onStartCam(thor::ActionContext < string > context)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    clickX = mousePosition.x;
    clickY = mousePosition.y;
    int cameraX = engine->getView()->getCenter().x;
    int cameraY = engine->getView()->getCenter().y;
    m->setCamOrigine(cameraX, cameraY);
    moveCam = true;
}

void Controleur::onStopCam(thor::ActionContext < string > context)
{
    (void) context;
    int cameraX = engine->getView()->getCenter().x;
    int cameraY = engine->getView()->getCenter().y;
    m->setCamOrigine(cameraX, cameraY);
    moveCam = false;
}

void Controleur::onMoveCamera(thor::ActionContext < string > context)
{
    if (!moveCam) //bug si exécuté avant le rightPress
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    int dx = clickX - mousePosition.x;
    int dy = clickY - mousePosition.y;
    int cameraL = engine->getView()->getSize().x;
    int cameraH = engine->getView()->getSize().y;
    m->moveView(dx, dy, cameraL, cameraH);
}

void Controleur::onZoom(thor::ActionContext < string > context)
{
    int ticks = context.event->mouseWheel.delta;
    m->zoom(ticks);
    
    //dimensions camera une fois le zoom effectué
    int cameraL = engine->getView()->getSize().x;
    int cameraH = engine->getView()->getSize().y;
    //deplacement nul pour éviter que le champ de la cam déborde de la map
    m->moveView(0, 0, cameraL, cameraH);
}

bool Controleur::onWindowResized(thor::ActionContext<string> context)
{
    m->windowResized(context.event->size.width, context.event->size.height);
    return true;
}

void Controleur::onResetZoom(thor::ActionContext < string > context)
{
    (void) context;
    m->resetZoom();
}

int Controleur::getX(int mouseX)
{
    int x_view = engine->getView()->getCenter().x - engine->getView()->getSize().x / 2;
    float coeff_x = engine->getView()->getSize().x / engine->getFenetre()->getSize().x;
    int x_absolu = x_view + mouseX * coeff_x;
    return x_absolu;
}

int Controleur::getY(int mouseY)
{
    int y_view = engine->getView()->getCenter().y - engine->getView()->getSize().y / 2;
    float coeff_y = engine->getView()->getSize().y / engine->getFenetre()->getSize().y;
    int y_absolu = y_view + mouseY * coeff_y;
    return y_absolu;
}

void Controleur::onMoveUnit(thor::ActionContext < string > context)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    sf::Vector2i movePosition = sf::Vector2i(getX(mousePosition.x), getY(mousePosition.y));
    m->moveUnitSelection(movePosition);
}

void Controleur::selectionOn(thor::ActionContext < string > context)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    m->initSelection(getX(mousePosition.x), getY(mousePosition.y));
}

void Controleur::selectionMove(thor::ActionContext < string > context)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    m->moveSelection(getX(mousePosition.x), getY(mousePosition.y));
}

void Controleur::selectionOff(thor::ActionContext < string > context)
{
    (void) context;
    m->endSelection();
}

}
