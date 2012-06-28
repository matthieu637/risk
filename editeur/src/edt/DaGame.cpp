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
    cce::MoteurSFML* ms = new cce::MoteurSFML("**Editeur Risk**");
    //GUI (CEGUI) doit être créer après SFML
    GUI* g = new GUI("Editeur.layout");
    
    modele = new Modele();
    vue = new Vue(ms, g);
    control = new Controleur(ms, modele, g);
    g->init(modele, control);
    
    // si segfault sur un element du menu, décommenter
    //control->setGUI(g); //FIXME WTF?
    
    
    modele->addVue(vue);
    modele->resetZoom();
    modele->moveView(ms->getFenetre()->getSize().x/2,ms->getFenetre()->getSize().y/2 - 25,0,0);
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
