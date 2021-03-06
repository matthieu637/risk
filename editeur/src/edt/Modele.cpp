#include "edt/Modele.hpp"
#include "edt/Vue.hpp"
#include "edt/Carte.hpp"
#include "edt/Pays.hpp"
#include "cce/Tile.hpp"
#include "edt/Region.hpp"
#include "cce/Repere.hpp"
#include "edt/Vue.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/ImageManager.hpp"
#include "cce/Decor.hpp"
#include <list>
#include <string>
#include <CEGUI/CEGUI.h>
#include <bib/StringUtils.hpp>
#include "cce/MoteurSFML.hpp"
#include <Thor/Multimedia/Shapes.hpp>

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

    poly = nullptr;
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
    string retour = cce::Modele::openCarte(chemin);
    reloadGUI();
    return retour;
}

void Modele::reloadGUI()
{
    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)*it)->reloadGUI();
}

string Modele::getCurrentMap() {
    return current_map;
}

void Modele::nouvelleCarte()
{
    current_map = "";
    delete carte;
    carte =  bib::XMLEngine::load<cce::Carte>("CARTE","data/map/empty.map");
    reloadGUI();
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

void Modele::setPoly(sf::ConvexShape* poly) {
    poly->setOutlineColor(sf::Color::Red);
    poly->setOutlineThickness(3.);
    poly->setFillColor(sf::Color(100,100,100,100));
    this->poly = poly;
}

void Modele::unsetPoly()
{
    poly = nullptr;
}

bool Modele::movePoly(int x_, int y_)
{
    if(poly != nullptr) {
        int index = poly->getPointCount();
        if(index != 0) {
            //poly->setPointCount(index);
            poly->setPoint(index-1, sf::Vector2f(x_, y_));
        }
        return true;
    }
    return false;
}

bool Modele::addPoint(int x, int y)
{
    if(poly != nullptr) {
        int nb = poly->getPointCount();
        if(nb != 0) {
            sf::Vector2f v = poly->getPoint(nb - 2);
            if((int)v.x == x && (int)v.y == y)
                return true;
        }
        poly->setPointCount(nb+1);
        poly->setPoint(nb, sf::Vector2f(x, y));
        if(nb == 0) {
            poly->setPointCount(nb+2);
            poly->setPoint(nb+1, sf::Vector2f(x, y));
        }
        return true;
    }
    return false;
}

void Modele::quit() {
    for (it = vues.begin(); it != vues.end(); it++) {
        ((Vue*)*it)->quit();
    }
}

void Modele::setCamOrigine(int cameraX, int cameraY) {
    cameraOrigineX = cameraX;
    cameraOrigineY = cameraY;
}

void Modele::moveView(int dx, int dy)
{
    int x = cameraOrigineX + dx * coeff_zoom;
    int y = cameraOrigineY + dy * coeff_zoom;
    int x_max = carte->getRepere()->largeur_pixels;
    int y_max = carte->getRepere()->hauteur_pixels;

    if (x < 0)
      x = 0;
    if (x > x_max)
      x = x_max;
    if (y < 0)
      y = 0;
    if (y > y_max)
      y = y_max;

    for(it = vues.begin(); it != vues.end(); it++)
      (*it)->updateCameraPosition(x, y);
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
    carte->getCoucheDecor()->moveDecor(dx, dy);
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
    cce::Decor* new_spawn = (cce::Decor*)carte->getCoucheDecor()->getDecor(x, y);
    cce::Decor* old_spawn;
    if(new_spawn != nullptr) {
        old_spawn = (cce::Decor*)carte->getPays(current_pays)->getPointSpawn();
        if(old_spawn != nullptr)
            old_spawn->setColor(sf::Color(255,255,255,255));
        new_spawn->setColor(sf::Color(255, 0, 0, 255));
        carte->getPays(current_pays)->setSpawn(new_spawn);
    }
}

void Modele::setFlag(int x, int y)
{
    cce::Decor* new_flag = (cce::Decor*)carte->getCoucheDecor()->getDecor(x, y);
    cce::Decor* old_flag;
    
    if(new_flag != nullptr) {
        old_flag = (cce::Decor*)carte->getRegion(current_region)->getFlag();
        if(old_flag != nullptr)
            old_flag->setColor(sf::Color(255,255,255,255));
        new_flag->setColor(sf::Color(255, 0, 0, 255));
        ((edt::Region*) carte->getRegion(current_region))->setFlag(new_flag);
    }
}

void Modele::setCurrentPays(const string& nom)
{
    cce::Pays* p;
    cce::Decor* d;

    //décoloriser spawn du pays courant
    p = carte->getPays(current_pays);
    if(p != nullptr) {
        d = p->getPointSpawn();
        if(d != nullptr)
            d->setColor(sf::Color(255,255,255,255));
    }

    //coloriser spawn du pays sélectionné
    p = carte->getPays(nom);
    if(p != nullptr) {
        d = p->getPointSpawn();
        if(d != nullptr)
            d->setColor(sf::Color(255, 0, 0, 255));
    }
    current_pays = nom;
}

void Modele::setCurrentRegion(const string& nom)
{
    cce::Region* r;
    cce::Decor* d;

    //décoloriser flag de la région courante
    r= carte->getRegion(current_region);
    if(r != nullptr) {
        d = r->getFlag();
        if(d != nullptr)
            d->setColor(sf::Color(255,255,255,255));
    }

    //coloriser flag de la région sélectionnée
    r = carte->getRegion(nom);
    if(r != nullptr) {
        d = r->getFlag();
        if(d != nullptr)
            d->setColor(sf::Color(255, 0, 0, 255));
    }
    current_region = nom;
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

void Modele::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    cce::Modele::draw(target, states);
    if(poly != nullptr) {
        target.draw(*poly, states);
    }
}


}
