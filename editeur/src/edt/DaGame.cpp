#include "edt/DaGame.hpp"
#include "edt/GUI.hpp"
#include <cce/ImageManager.hpp>
#include <cce/MoteurSFML.hpp>

namespace edt {

DaGame::DaGame()
{
    cce::MoteurSFML* ms = new cce::MoteurSFML();
    //GUI (CEGUI) doit être créer après SFML
    GUI* g = new GUI();
    
    modele = new Modele();
    vue = new Vue(ms, g);
    control = new Controleur(ms, modele, g);
    
    modele->addVue(vue);
}

void DaGame::gameloop()
{
    while(control->isRunning()) {
        control->appliquer_events();
        modele->update();
        vue->dessiner(modele);
    }
}

}
