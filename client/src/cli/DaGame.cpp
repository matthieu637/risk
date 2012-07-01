#include "cli/DaGame.hpp"
#include "cli/GUI.hpp"
#include <cce/ImageManager.hpp>
#include <cce/MoteurSFML.hpp>
#include "cli/Modele.hpp"
#include "cli/Vue.hpp"
#include "cli/Controleur.hpp"

namespace cli {

DaGame::DaGame()
{
    cce::MoteurSFML* ms = new cce::MoteurSFML("**Client Risk**");
    //GUI (CEGUI) doit être créer après SFML
    GUI* g = new GUI("Client.layout");
    
    modele = new Modele();
    vue = new Vue(ms, g);
    control = new Controleur(ms, modele, g);
    g->init(modele);
    
    modele->addVue(vue);
    modele->resetZoom();
    modele->setCamOrigine(ms->getView()->getSize().x/2, ms->getView()->getSize().y/2);
    modele->moveView(0, 0, ms->getView()->getSize().x, ms->getView()->getSize().y);
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
