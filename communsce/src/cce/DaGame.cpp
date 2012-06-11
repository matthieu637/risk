#include "cce/DaGame.hpp"
#include "cce/MoteurSFML.hpp"
#include "cce/GUI.hpp"

namespace cce {

DaGame::DaGame()
{
    MoteurSFML* ms = new MoteurSFML();
    GUI* g = new GUI();

    vue.init(ms, g);
    control.init(ms, g);
    modele.init(ms);
}

void DaGame::gameloop() {
    while(true) {
        control.appliquer_events(modele);
        modele.update();
        vue.dessiner(modele);
    }
}

}
