#include "edt/DaGame.hpp"
#include "edt/GUI.hpp"
#include <cce/ImageManager.hpp>
#include <cce/MoteurSFML.hpp>
#include "edt/Modele.hpp"
#include "edt/Vue.hpp"
#include "edt/Controleur.hpp"

namespace edt {

DaGame::DaGame()
{
    cce::MoteurSFML* ms = new cce::MoteurSFML();
    //GUI (CEGUI) doit être créer après SFML
    GUI* g = new GUI("Editeur.layout");
    
    modele = new Modele();
    vue = new Vue(ms, g);
    control = new Controleur(ms, modele, g);
    g->init(modele);
    
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
