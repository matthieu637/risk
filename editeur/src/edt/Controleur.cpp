#include "edt/Controleur.hpp"
#include "edt/Modele.hpp"
#include "edt/GUI.hpp"
#include "cce/MoteurSFML.hpp"
#include <cce/CppScriptModule.hpp>
#include "edt/Console.hpp"
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

namespace edt {

Controleur::Controleur(cce::MoteurSFML * engine, Modele * m, GUI * gui):cce::Controleur(engine, gui) {
    this->m = m;
    selection = false;
    moveDecor = false;
    setSpawn = false;
    setFlag = false;

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
    Action c_press(sf::Keyboard::C, Action::ReleaseOnce);
    Action d_press(sf::Keyboard::D, Action::ReleaseOnce);
    Action p_press(sf::Keyboard::P, Action::ReleaseOnce);
    Action r_press(sf::Keyboard::R, Action::ReleaseOnce);
    Action escape_press(sf::Keyboard::Escape, Action::ReleaseOnce);
    Action t_press(sf::Keyboard::T, Action::ReleaseOnce);
    Action rctrl_press(sf::Keyboard::RControl, Action::Hold);
    Action num0_press(sf::Keyboard::Num0, Action::Hold);
    Action rctrl_num0 = rctrl_press && num0_press;
    Action ctrl_hold(sf::Keyboard::LControl, Action::Hold);
    Action z_hold(sf::Keyboard::Z, Action::Hold);
    Action y_hold(sf::Keyboard::Y, Action::Hold);

    // Map
    map["quit"] = close;
    map["zoom"] = molette;
    map["resize"] = resize;
    map["reset_zoom"] = rctrl_num0;
    map["start_cam"] = wheel_press;
    map["stop_cam"] = wheel_release;
    map["move_camera"] = drag_wheel;
    map["start_move_decor"] = left_press;
    map["stop_move_decor"] = left_release;
    map["set_spawn"] = left_release;
    map["set_flag"] = left_release;
    map["move_decor"] = drag_left;
    map["placer_objet"] = drag_left || left_release;
    map["supprimer_objet"] = right_release;
    map["selection"] = space_press;
    map["choix_palette"] = t_press || d_press || p_press || r_press;
    map["console"] = c_press;
    map["close_gui"] = escape_press;
    map["move_poly"] = mouse_move;
    map["add_point_poly"] = left_release;
    map["undo"] = ctrl_hold && z_hold;
    map["redo"] = ctrl_hold && y_hold;  
     
    //Binding map-fonctions
    system.connect("start_cam", BIND(&Controleur::onStartCam));
    system.connect("stop_cam", BIND(&Controleur::onStopCam));
    system.connect("move_camera", BIND(&Controleur::onMoveCamera));
    system.connect("start_move_decor", BIND(&Controleur::onStartMoveDecor));
    system.connect("stop_move_decor", BIND(&Controleur::onStopMoveDecor));
    system.connect("move_decor", BIND(&Controleur::onMoveDecor));
    system.connect("zoom", BIND(&Controleur::onZoom));
    system.connect("reset_zoom", BIND(&Controleur::onResetZoom));
    system.connect("placer_objet", BIND(&Controleur::onPlaceObject));
    system.connect("supprimer_objet", BIND(&Controleur::onDeleteObject));
    system.connect("selection", BIND(&Controleur::onSelectionThor));
    system.connect("resize", BIND(&Controleur::onWindowResized));
    system.connect("choix_palette", BIND(&Controleur::onChoixPaletteThor));
    system.connect("console", BIND(&Controleur::onOpenConsole));
    system.connect("close_gui", BIND(&Controleur::onCloseGUI));
    system.connect("set_spawn", BIND(&Controleur::onChooseSpawn));
    system.connect("set_flag", BIND(&Controleur::onChooseFlag));
    system.connect("move_poly", BIND(&Controleur::onMovePoly));
    system.connect("add_point_poly", BIND(&Controleur::onAddPoint));
    system.connect("undo", BIND(&Controleur::onUndoThor));
    system.connect("redo", BIND(&Controleur::onRedoThor));   
    
    //Binding fonctions CEGUI
    moduleGUI->ajouterHandler("quitter", BIND(&Controleur::onQuit));
    moduleGUI->ajouterHandler("selection", BIND(&Controleur::onSelection));
    moduleGUI->ajouterHandler("gui_viewscroll_change_vertical", BIND(&Controleur::onMainScrollVertChange));
    moduleGUI->ajouterHandler("gui_viewscroll_change_horizontal", BIND(&Controleur::onMainScrollHoriChange));
    moduleGUI->ajouterHandler("enregistrerSous", BIND(&Controleur::onSaveAs));
    moduleGUI->ajouterHandler("enregistrer", BIND(&Controleur::onSave));
    moduleGUI->ajouterHandler("ouvrir", BIND(&Controleur::onOpen));
    moduleGUI->ajouterHandler("console", BIND(&Controleur::onOpenConsoleClick));
    moduleGUI->ajouterHandler("choix_palette", BIND(&Controleur::onChoixPalette));
    moduleGUI->ajouterHandler("redimensionner", BIND(&Controleur::onRedimensionner));
    moduleGUI->ajouterHandler("new_map", BIND(&Controleur::onNewMap));
    moduleGUI->ajouterHandler("undo", BIND(&Controleur::onUndo));
    
    gui->setScriptModule(moduleGUI);
}

void Controleur::setGUI(GUI* g) {
    this->gui = g;
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
    int cameraX = engine->getView()->getCenter().x;
    int cameraY = engine->getView()->getCenter().y;
    m->setCamOrigine(cameraX, cameraY);
    moveCam = false;
}

void Controleur::onMoveCamera(thor::ActionContext < string > context) {
    if (!moveCam) //bug si exécuté avant le rightPress
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    int dx = clickX - mousePosition.x;
    int dy = clickY - mousePosition.y;
    m->moveView(dx, dy);
}

void Controleur::onStartMoveDecor(thor::ActionContext < string > context) {
    if(!selection)
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    clickX = getX(mousePosition.x);
    clickY = getY(mousePosition.y);
    m->setDecorMove(clickX, clickY);
    moveDecor = true;
}

void Controleur::onStopMoveDecor(thor::ActionContext < string > context) {
    (void) context;
    moveDecor = false;
}

void Controleur::onMoveDecor(thor::ActionContext < string > context) {
    if (!moveDecor) //bug si exécuté avant le leftPress
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    int dx = getX(mousePosition.x) - clickX;
    int dy = getY(mousePosition.y) - clickY;

    m->moveDecor(dx, dy);

    clickX = getX(mousePosition.x);
    clickY = getY(mousePosition.y);
}

void Controleur::onZoom(thor::ActionContext < string > context) {
    int ticks = context.event->mouseWheel.delta;
    m->zoom(ticks);
}

bool Controleur::onWindowResized(thor::ActionContext<string> context) {
    m->windowResized(context.event->size.width, context.event->size.height);
    return true;
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

void Controleur::onSelectionThor(thor::ActionContext < string > context) {
    (void) context;
    CEGUI::Checkbox *cb = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingleton().getWindow("Edition/Selection/Check");
    cb->setSelected(!cb->isSelected());
}

void Controleur::onChoixPaletteThor(thor::ActionContext < string > context) {
    sf::Event::KeyEvent key = context.event->key;
    CEGUI::FrameWindow* mi;

    if(key.code == sf::Keyboard::T)
        mi = (CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("Palettes/Terrains");
    else if(key.code == sf::Keyboard::D)
	mi = (CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("Palettes/Decors");
    else if(key.code == sf::Keyboard::P)
	mi = (CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("Palettes/Pays");
    else if(key.code == sf::Keyboard::R)
	mi = (CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("Palettes/Regions");
    
    CEGUI::WindowEventArgs wea = CEGUI::WindowEventArgs(mi);
    onChoixPalette(wea);
}

void Controleur::onChooseSpawn(thor::ActionContext < string > context) {
    if(!setSpawn)
      return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    m->setSpawn(getX(mousePosition.x), getY(mousePosition.y));
    setSpawn = false;
}

void Controleur::onChooseFlag(thor::ActionContext < string > context) {
    if(!setFlag)
      return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*context.window);
    m->setFlag(getX(mousePosition.x), getY(mousePosition.y));
    setFlag = false;
}

bool Controleur::onMovePoly(thor::ActionContext < string > context)
{
    return m->movePoly(getX(context.event->mouseMove.x), getY(context.event->mouseMove.y));
}

bool Controleur::onAddPoint(thor::ActionContext < string > context)
{
    return m->addPoint(getX(context.event->mouseButton.x), getY(context.event->mouseButton.y));
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

bool Controleur::onSetSpawn(const CEGUI::EventArgs &e)
{
    (void)e;
    setSpawn = true;
    return true;
}

bool Controleur::onSetFlag(const CEGUI::EventArgs &e)
{
    (void)e;
    setFlag = true;
    return true;
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
    else if(nom == "Palettes/Regions")
	m->selectPalette(regions);
    else if(nom == "Palettes/Pays")
        m->selectPalette(pays);
    return true;
}

bool Controleur::onQuit(const CEGUI::EventArgs & e) {
    (void) e;
    gui->getConsole()->afficherCommande("/quit");   
    return true;
}

bool Controleur::onSave(const CEGUI::EventArgs & e) {
    (void) e;
    gui->getConsole()->afficherCommande("/save "+m->getCurrentMap());
    return true;
}

bool Controleur::onSaveAs(const CEGUI::EventArgs & e) {
    (void) e;
    gui->getConsole()->afficherCommande("/save ");
    return true;
}

bool Controleur::onOpen(const CEGUI::EventArgs & e) {
    (void) e;
    gui->getConsole()->afficherCommande("/open ");
    return true;
}

bool Controleur::onOpenConsole(thor::ActionContext < string > context){
    sf::Event::KeyEvent key = context.event->key;
    CEGUI::FrameWindow* mi;

    if(key.code == sf::Keyboard::C){
	mi = (CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("Outils/Console");
	CEGUI::WindowEventArgs wea = CEGUI::WindowEventArgs(mi);
	onOpenConsoleClick(wea);
    }
    return true;
}

bool Controleur::onCloseGUI(thor::ActionContext < string > context){
    (void)context;
    gui->getConsole()->setVisible(false);
    ((edt::GUI*) gui)->hidePalette();
    return true;
}

bool Controleur::onOpenConsoleClick(const CEGUI::EventArgs& e){
    (void) e;
    gui->getConsole()->setVisible(true);
    return true;
}

bool Controleur::onRedimensionner(const CEGUI::EventArgs& e){
    (void) e;
    gui->getConsole()->afficherCommande("/redimensionner");
    return true;  
}

bool Controleur::onNewMap(const CEGUI::EventArgs & e) {
    (void) e;
    gui->getConsole()->afficherCommande("/new_map");
    return true;
}

void Controleur::onUndoThor(thor::ActionContext < string > context){
    (void)context;
    const CEGUI::EventArgs ma;
    this->onUndo(ma);
}

bool Controleur::onUndo(const CEGUI::EventArgs & e) {
    (void) e;
    m->getCarte()->getCoucheDecor()->undoDecor();

    return true;
}

void Controleur::onRedoThor(thor::ActionContext < string > context){
    (void)context;
    const CEGUI::EventArgs ma;
    this->onRedo(ma);
}


bool Controleur::onRedo(const CEGUI::EventArgs & e) {
    (void) e;
    m->getCarte()->getCoucheDecor()->redoDecor();

    return true;
}


bool Controleur::onSelection(const CEGUI::EventArgs & e) {
    (void) e;
    selection = !selection;
    return true;
}

bool Controleur::onMainScrollVertChange(const CEGUI::EventArgs & e) {
    const CEGUI::WindowEventArgs& wea = static_cast<const CEGUI::WindowEventArgs&>(e);
    CEGUI::Scrollbar* sb = static_cast<CEGUI::Scrollbar*>(wea.window);

    m->moveScrollVert(sb->getScrollPosition());
    return true;
}

bool Controleur::onMainScrollHoriChange(const CEGUI::EventArgs & e) {
    const CEGUI::WindowEventArgs& wea = static_cast<const CEGUI::WindowEventArgs&>(e);
    CEGUI::Scrollbar* sb = static_cast<CEGUI::Scrollbar*>(wea.window);

    m->moveScrollHori(sb->getScrollPosition());
    return true;
}

}
