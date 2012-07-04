#ifndef CONTROLEUREDITEUR_HPP
#define CONTROLEUREDITEUR_HPP
#include <cce/Controleur.hpp>
#include <string>
#include <CEGUI/CEGUIEventArgs.h>
#include <Thor/Events/ActionMap.hpp>
#include <Thor/Events/EventSystem.hpp>

using std::string;

///
///\file Controleur.hpp
///\brief Controleur du MVC principale, il sert à dispatcher et traiter les évènements
///\author matthieu, aymeric
///

namespace cce {
class MoteurSFML;
} 

namespace cli {

class Modele;
class GUI;

class Controleur:public cce::Controleur {

public:
///
///\brief Simple setter, engine et gui doivent être les mêmes que celui de la vue
///
    Controleur(cce::MoteurSFML * engine, Modele * m, GUI * gui);

    void onStartCam(thor::ActionContext < string > context);
    void onStopCam(thor::ActionContext < string > context);
    void onMoveCamera(thor::ActionContext < string > context);
    void onZoom(thor::ActionContext < string > context);
    void onResetZoom(thor::ActionContext < string > context);
    bool onWindowResized(thor::ActionContext<string> context);
    void onMoveUnit(thor::ActionContext < string > context);
    bool onQuit(const CEGUI::EventArgs & e);
    void onLeftClick(thor::ActionContext < string > context);
    void selectionOff(thor::ActionContext < string > context);
    void selectionMove(thor::ActionContext < string > context);
    void shiftOn(thor::ActionContext < string > context);
    void shiftOff(thor::ActionContext < string > context);
    void prepareAttack(thor::ActionContext < string > context);
    void onattack(thor::ActionContext < string > context);
    void onOpenConsole(thor::ActionContext < string > context);
    void onCloseConsole(thor::ActionContext < string > context);
    
    int getX(int mouseX);
    int getY(int mouseY);
    
    void spawnUnit(thor::ActionContext < string > context);

      
    bool getAttackMode();
    void setAttackMode(bool b);
    
private:
    int clickX, clickY;
    bool moveCam, moveDecor;

    bool attackMode;
    bool selectionRemove;
    
    //variables privées necessaires à la détection d'Action pour des Action à touches multiples
    bool shiftBool;
  
   // GUI *gui;
    Modele *m;
};

}
#endif	// CONTROLEUR_HPP
