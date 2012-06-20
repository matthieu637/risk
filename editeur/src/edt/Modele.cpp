#include "edt/Modele.hpp"
#include "edt/Vue.hpp"
#include "edt/Carte.hpp"
#include "cce/Tile.hpp"
#include "cce/Repere.hpp"
#include "edt/Vue.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/ImageManager.hpp"
#include <list>
#include <string>
#include <CEGUI/CEGUI.h>

using std::list;
using std::string;

namespace edt {

Modele::Modele():cce::Modele() {
    // carte = new Carte(50,50);
    // bib::XMLEngine::save<Carte>(*carte, "Carte", "alpha.map");

    carte = bib::XMLEngine::load < edt::Carte > ("Carte", "data/map/sf/alpha.map");
    coeff_zoom = 1;
    tt = cce::Univers::getInstance()->getTileTemplate(100000000);
    dt = cce::Univers::getInstance()->getDecorTemplate(200000000);
    current_pays = "Mordor";
    tile = true;
    decor = false;
}

Modele::~Modele() {

}

void Modele::update() {
    cce::Modele::update();
}

Repere *Modele::getRepere() {
    return (Repere *) carte->getRepere();
}

void Modele::saveCarte(const std::string & chemin) {
    (void) chemin;
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

    vues.end();
    for (it = vues.begin(); it != vues.end(); it++)
        (*it)->updateCameraPosition(x, y);
}

void Modele::zoom(int ticks) {
    coeff_zoom *= 1 - ticks * 0.05;
    for (it = vues.begin(); it != vues.end(); it++)
        (*it)->updateCameraZoom(1 - ticks * 0.05);
}

void Modele::resetZoom() {
    coeff_zoom = 1;
    for (it = vues.begin(); it != vues.end(); it++)
        (*it)->resetCameraZoom();
}

void Modele::setTileTemplate(int id)
{
    tt = cce::Univers::getInstance()->getTileTemplate(id);
}

void Modele::setDecorTemplate(int id)
{
    dt = cce::Univers::getInstance()->getDecorTemplate(id);
}

void Modele::placeObject(int x, int y) {
  if(tile)
    getRepere()->setTile(tt, x, y);
  else if(decor)
    carte->getCoucheDecor()->addDecor(dt, x, y);
}

void Modele::deleteObject(int x, int y) {
  if(tile)
    getRepere()->unsetTile(x, y);
  else if(decor)
    carte->getCoucheDecor()->removeDecor(x, y);
}

void Modele::selectPalette(palette_type p)
{
    ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Tiles"))->setVisible(false);
    ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Decors"))->setVisible(false);
    tile = false;
    decor = false;
    switch(p)
    {
	case tiles:
	  ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Tiles"))->setVisible(true);
	  tile = true;
	  break;
	case decors:
	  ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Decors"))->setVisible(true);
	  decor = true;
	  break;
    }
}

void Modele::addRegion(string nom)
{
    (void) nom;
// 	carte->addRegion(current_pays, nom);
    //FIXME pointeurs getListRegions
    /*list<string> noms;

    list<cce::Region>::iterator ir =  carte->getListRegions()->begin();
    for (; ir != carte->getListRegions()->end(); ir++)
        noms.push_back((*ir).getNom());

    list <cce::Vue*>::iterator it;
    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)(*it))->updateListRegions(noms);
    */

}

void Modele::moveScrollVert(float pos, float size)
{
    float npos = pos/100 * (carte->getRepere()->getHauteur() - size/cce::Repere::h_tile) + size/2;

    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)(*it))->updateScrollVert(npos);
}

void Modele::moveScrollHori(float pos, float size)
{
    float npos = pos/100 * (carte->getRepere()->getLargeur() - size/cce::Repere::l_tile) + size /2;

    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)(*it))->updateScrollHori(npos);
}

}