#include "edt/DaGame.hpp"
#include "edt/GUI.hpp"
#include <cce/ImageManager.hpp>
#include <cce/MoteurSFML.hpp>

namespace edt {

DaGame::DaGame()
{
    GUI* g = new GUI();
    cce::MoteurSFML* ms = new cce::MoteurSFML();
    
    modele = new Modele();
    vue = new Vue(ms, g);
    control = new Controleur(ms, modele, g);
    
    modele->addVue(vue);
}

void DaGame::gameloop()
{
    while(true) {
        control->appliquer_events();
        modele->update();
        vue->dessiner(modele);
    }
}

}
