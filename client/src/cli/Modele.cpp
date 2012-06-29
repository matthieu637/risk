#include "cli/Modele.hpp"
#include "cli/Vue.hpp"
#include <cli/Unit.hpp>
#include "cce/Tile.hpp"
#include "cce/Repere.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/ImageManager.hpp"
#include <list>
#include <string>
#include <CEGUI/CEGUI.h>

using std::list;
using std::string;

namespace cli {

Modele::Modele():cce::Modele() {
    // carte = new Carte(50,50);
    // bib::XMLEngine::save<Carte>(*carte, "Carte", "alpha.map");

    carte = bib::XMLEngine::load < cce::Carte > ("Carte", "data/map/sf/alpha.map");
    // carte = new Carte; FIXME
    coeff_zoom = 1;
    spawnUnit(300000000,40,40);
}

Modele::~Modele() {

}

void Modele::update() {
    cce::Modele::update();
}

void Modele::spawnUnit(int id, int x, int y) {
   Unit* u = new Unit;
   u->setId(id);
   u->setPosition(x,y);
   carte->getCoucheDecor()->addDecor(u);
 
}

void Modele::setCamOrigine(int cameraX, int cameraY) {
    cameraOrigineX = cameraX;
    cameraOrigineY = cameraY;
}

void Modele::moveView(int dx, int dy, int cameraX, int cameraY) {
    int x = cameraOrigineX + dx * coeff_zoom;
    int y = cameraOrigineY + dy * coeff_zoom;
    int x_max = carte->getRepere()->getLargeur() * 158;
    int y_max = carte->getRepere()->getHauteur() * 44;

    if ((x < 0 && cameraX < 0) || (x > x_max && cameraX > x_max))
        x = cameraX;
    if ((y < 0 && cameraY < 0) || (y > y_max && cameraY > y_max))
        y = cameraY;

    for (it = vues.begin(); it != vues.end(); it++) {
        (*it)->updateCameraPosition(x, y);
    }

}

void Modele::zoom(int ticks) {
    coeff_zoom *= 1 - ticks * 0.05;
    for (it = vues.begin(); it != vues.end(); it++) {
        ((Vue*)*it)->updateCameraZoom(1 - ticks * 0.05);
    }
}

void Modele::resetZoom() {
    coeff_zoom = 1;
    for (it = vues.begin(); it != vues.end(); it++) {
        (*it)->resetCameraZoom();
    }
}

void Modele::windowResized(int width, int height)
{
    for (it = vues.begin(); it != vues.end(); it++) {
        ((Vue*)(*it))->updateSize(width, height);
    }
    resetZoom();
}

}
