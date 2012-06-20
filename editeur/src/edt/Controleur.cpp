#include "edt/Controleur.hpp"
#include "edt/Modele.hpp"
#include "edt/GUI.hpp"
#include "cce/MoteurSFML.hpp"
#include <cce/CppScriptModule.hpp>
#include <cce/Console.hpp>
#include <SFML/Window/Event.hpp>
#include <CEGUI/elements/CEGUIScrollbar.h>
#include <CEGUI/elements/CEGUIFrameWindow.h>
#include <Thor/Events/Action.hpp>
#include <Thor/Events/EventSystem.hpp>
#include "bib/Logger.hpp"

using thor::Action;

namespace edt {

Controleur::Controleur(cce::MoteurSFML * engine, Modele * m, GUI * gui):cce::Controleur(engine, gui) {
    this->m = m;
    selection = false;

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
    map["supprimer_objet"] = right_release;

    //Binding map-fonctions
    system.connect("start_cam", BIND(&Controleur::onStartCam));
    system.connect("stop_cam", BIND(&Controleur::onStopCam));
    system.connect("move_camera", BIND(&Controleur::onMoveCamera));
    system.connect("zoom", BIND(&Controleur::onZoom));
    system.connect("reset_zoom", BIND(&Controleur::onResetZoom));
    system.connect("placer_objet", BIND(&Controleur::onPlaceObject));
    system.connect("supprimer_objet", BIND(&Controleur::onDeleteObject));

    //Binding fonctions CEGUI
    moduleGUI->ajouterHandler("quitter", BIND(&Controleur::onQuit));
    moduleGUI->ajouterHandler("selection", BIND(&Controleur::onSelection));
    moduleGUI->ajouterHandler("gui_viewscroll_change_vertical",  BIND(&Controleur::onMainScrollVertChange));
    moduleGUI->ajouterHandler("gui_viewscroll_change_horizontal",  BIND(&Controleur::onMainScrollHoriChange));
    moduleGUI->ajouterHandler("enregistrer", BIND(&Controleur::onSave));
    moduleGUI->ajouterHandler("ouvrir", BIND(&Controleur::onOpen));
    moduleGUI->ajouterHandler("choix_palette", BIND(&Controleur::onChoixPalette));
    
    gui->setScriptModule(moduleGUI);
}
void Controleur::onStartCam(thor::ActionContext < string > context) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    clickX = mousePosition.x;
    clickY = mousePosition.y;
    int cameraX = engine->getView()->getCenter().x;
    int cameraY = engine->getView()->getCenter().y;
    m->setCamOrigine(cameraX, cameraY);
    moveCam = true;
}

void Controleur::onStopCam(thor::ActionContext < string > context) {
    (void) context;
    moveCam = false;
}

void Controleur::onMoveCamera(thor::ActionContext < string > context) {
    if (!moveCam)		//bug si exécuté avant le rightPress
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    int dx = clickX - mousePosition.x;
    int dy = clickY - mousePosition.y;
    int cameraX = engine->getView()->getCenter().x;
    int cameraY = engine->getView()->getCenter().y;
    m->moveView(dx, dy, cameraX, cameraY);
}

void Controleur::onZoom(thor::ActionContext < string > context) {
    int ticks = context.event->mouseWheel.delta;
    m->zoom(ticks);
}

void Controleur::onResetZoom(thor::ActionContext < string > context) {
    (void) context;
    m->resetZoom();
}

void Controleur::onPlaceObject(thor::ActionContext < string > context) {
    if (selection)
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    m->placeObject(getX(mousePosition.x), getY(mousePosition.y));
}

void Controleur::onDeleteObject(thor::ActionContext < string > context) {
    if (!selection)
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    m->deleteObject(getX(mousePosition.x), getY(mousePosition.y));
}

int Controleur::getX(int mouseX) {
    int x_view = engine->getView()->getCenter().x - engine->getView()->getSize().x / 2;
    float coeff_x = engine->getView()->getSize().x / engine->getFenetre()->getSize().x;
    int x_absolu = x_view + mouseX * coeff_x;
    return x_absolu;
}

int Controleur::getY(int mouseY) {
    int y_view = engine->getView()->getCenter().y - engine->getView()->getSize().y / 2;
    float coeff_y = engine->getView()->getSize().y / engine->getFenetre()->getSize().y;
    int y_absolu = y_view + mouseY * coeff_y;
    return y_absolu;
}

bool Controleur::onChoixPalette(const CEGUI::EventArgs & e)
{
    const CEGUI::WindowEventArgs& wea = static_cast<const CEGUI::WindowEventArgs&>(e);
    CEGUI::FrameWindow* fw = static_cast<CEGUI::FrameWindow*>(wea.window);
    const string nom = fw->getName().c_str();
    if(nom == "Palettes/Terrains")
      m->selectPalette(tiles);
    else if(nom == "Palettes/Decors")
      m->selectPalette(decors);
    return true;
}

bool Controleur::onQuit(const CEGUI::EventArgs & e) {
    (void) e;
    engine->getFenetre()->close();
    return true;
}

bool Controleur::onSave(const CEGUI::EventArgs & e) {
    (void) e;
    gui->getConsole()->afficherCommande("/save ");
    return true;
}

bool Controleur::onOpen(const CEGUI::EventArgs & e) {
    (void) e;
    gui->getConsole()->afficherCommande("/open ");
    return true;
}

bool Controleur::onSelection(const CEGUI::EventArgs & e) {
    (void) e;
    selection = !selection;
    return true;
}

bool Controleur::onMainScrollVertChange(const CEGUI::EventArgs & e){
    const CEGUI::WindowEventArgs& wea = static_cast<const CEGUI::WindowEventArgs&>(e);
    CEGUI::Scrollbar* sb = static_cast<CEGUI::Scrollbar*>(wea.window);
    
    sf::View* v = engine->getView();
    
    m->moveScrollVert(sb->getScrollPosition(), v->getSize().y);
    return true;
}

bool Controleur::onMainScrollHoriChange(const CEGUI::EventArgs & e){
    const CEGUI::WindowEventArgs& wea = static_cast<const CEGUI::WindowEventArgs&>(e);
    CEGUI::Scrollbar* sb = static_cast<CEGUI::Scrollbar*>(wea.window);
    
    sf::View* v = engine->getView();
    
    m->moveScrollHori(sb->getScrollPosition(), v->getSize().x);
    return true;
}


}
