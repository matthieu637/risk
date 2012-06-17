#ifndef CONTROLEUREDITEUR_HPP
#define CONTROLEUREDITEUR_HPP
#include <cce/Controleur.hpp>
#include <string>
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

namespace edt {

class Modele;
class GUI;

class Controleur : public cce::Controleur
{

public:
///
///\brief Simple setter, engine et gui doivent être les mêmes que celui de la vue
///
    Controleur(cce::MoteurSFML* engine, Modele* m, GUI* gui);

    void onStartCam(thor::ActionContext<string> context);
    void onStopCam(thor::ActionContext<string> context);
    void onMoveCamera(thor::ActionContext<string> context);
    void onZoom(thor::ActionContext<string> context);
    void onResetZoom(thor::ActionContext<string> context);
    void onPlaceObject(thor::ActionContext<string> context);

private:
    int clickX, clickY;
    bool moveCam, tile, decor;
    GUI* gui;
    Modele* m;
};

}

#endif // CONTROLEUR_HPP
