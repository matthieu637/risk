#include "edt/Modele.hpp"
#include "edt/Vue.hpp"
#include "edt/Carte.hpp"
#include "cce/Tile.hpp"
#include "cce/Repere.hpp"
#include "edt/Vue.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/ImageManager.hpp"
#include "cce/Decor.hpp"
#include <list>
#include <string>
#include <CEGUI/CEGUI.h>
#include <bib/StringUtils.hpp>

using std::list;
using std::string;

namespace edt {

Modele::Modele():cce::Modele() {
    // carte = new Carte(50,50);
    // bib::XMLEngine::save<Carte>(*carte, "Carte", "alpha.map");

    carte = bib::XMLEngine::load < edt::Carte > ("Carte", "data/map/sf/alpha.map");
    // carte = new Carte; FIXME
    coeff_zoom = 1;
    tt = cce::Univers::getInstance()->getTileTemplate(100000000);
    dt = cce::Univers::getInstance()->getDecorTemplate(200000000);
   
    current_map = "";
    current_pays = "";
}

Modele::~Modele() {

}

void Modele::update() {
    cce::Modele::update();
}

Repere *Modele::getRepere() {
    return (Repere *) carte->getRepere();
}

//herite de edt::openCarte
string Modele::openCarte(const string& chemin) {
    current_map = chemin;
    return cce::Modele::openCarte(chemin);
}

string Modele::getCurrentMap() {
    return current_map;
}

void Modele::nouvelleCarte()
{
    current_map = "";
    delete carte;
    carte =  bib::XMLEngine::load<cce::Carte>("CARTE","data/map/empty.map");
}

 string Modele::saveCarte(const string& chemin) {
    current_map = chemin;
    bib::XMLEngine::save<cce::Carte>(*carte,"Carte",chemin);
    return "La carte "+chemin+" a bien été sauvegardée";
}


string Modele::saveCarte() {
    if(current_map != "" && !bib::onlySpaceCharacter(current_map)) {
        bib::XMLEngine::save<cce::Carte>(*carte,"Carte",current_map);
        return "La carte "+current_map+" a bien été sauvegardée";
    } else {
        return "Veuillez saisir un nom de carte";
    }
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
        ((Vue*)*it)->updateScrolls();
    }

}

void Modele::zoom(int ticks) {
    coeff_zoom *= 1 - ticks * 0.05;
    for (it = vues.begin(); it != vues.end(); it++) {
        ((Vue*)*it)->updateCameraZoom(1 - ticks * 0.05);
        ((Vue*)*it)->updateScrollsThumb(coeff_zoom, carte->getRepere()->getLargeur(), carte->getRepere()->getHauteur());
    }
}

void Modele::resetZoom() {
    coeff_zoom = 1;
    for (it = vues.begin(); it != vues.end(); it++) {
        (*it)->resetCameraZoom();
        ((Vue*)*it)->updateScrollsThumb(coeff_zoom, carte->getRepere()->getLargeur(), carte->getRepere()->getHauteur());
    }
}

void Modele::setTileTemplate(int id)
{
    tt = cce::Univers::getInstance()->getTileTemplate(id);
}

void Modele::setDecorTemplate(int id)
{
    dt = cce::Univers::getInstance()->getDecorTemplate(id);
}

void Modele::setDecorMove(int x, int y) {
    carte->getCoucheDecor()->setDecorMove(x, y);
}

void Modele::moveDecor(int dx, int dy) {
    carte->getCoucheDecor()->moveDecor(dx*coeff_zoom, dy*coeff_zoom);
}

void Modele::placeObject(int x, int y) {
    if(palette == tiles)
        getRepere()->setTile(tt, x, y);
    else if(palette == decors)
        carte->getCoucheDecor()->addDecor(dt, x, y);
}

void Modele::deleteObject(int x, int y) {
    if(palette == tiles)
        getRepere()->unsetTile(x, y);
    else if(palette == decors)
        carte->getCoucheDecor()->removeDecor(x, y);
}

void Modele::setSpawn(int x, int y)
{
    const cce::Decor* d = carte->getCoucheDecor()->getDecor(x, y);
    if(d != nullptr)
        ;
    //carte->getPays(current_pays)->setSpawn();
}

void Modele::setCurrentPays(string nom)
{
    current_pays = nom;
}

void Modele::selectPalette(palette_type p)
{
    ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Tiles"))->setVisible(false);
    ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Decors"))->setVisible(false);
    ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Regions"))->setVisible(false);
    ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Pays"))->setVisible(false);
    palette = p;
    switch(p)
    {
    case tiles:
        ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Tiles"))->setVisible(true);
        break;
    case decors:
        ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Decors"))->setVisible(true);
        break;
    case pays:
        ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Pays"))->setVisible(true);
        break;
    case regions:
        ((CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow("PaletteFrames/Regions"))->setVisible(true);
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

void Modele::windowResized(int width, int height)
{
    for (it = vues.begin(); it != vues.end(); it++) {
        ((Vue*)(*it))->updateSize(width, height);
    }
    resetZoom();
}

void Modele::moveScrollVert(float pos)
{
    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)(*it))->updateYCamera(pos);
}

void Modele::moveScrollHori(float pos)
{
    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)(*it))->updateXCamera(pos);
}

void Modele::redimensionner(int x, int y) {
    edt::Repere* r = static_cast<edt::Repere*> (getCarte()->getRepere());
    r->redimensionner(x, y);
    
    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)(*it))->initScrolls(x, y);
}


}
