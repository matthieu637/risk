#include "cce/DaGame.hpp"
#include "cce/GUI.hpp"
#include "cce/ImageManager.hpp"

namespace cce {

DaGame::DaGame()
{
    GUI* g = new GUI();
    MoteurSFML* ms = new MoteurSFML();
    
    modele = new Modele();
    vue = new Vue();
    control = new Controleur(ms, modele, g);
    vue->init(ms, g, modele);
}

void DaGame::gameloop() {
    while(true) {
        control->appliquer_events();
        modele->update();
        vue->dessiner(modele);
    }
}

}
