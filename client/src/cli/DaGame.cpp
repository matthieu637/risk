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
