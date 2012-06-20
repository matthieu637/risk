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

using std::list;
using std::string;

namespace edt {

    Modele::Modele():cce::Modele() {
	// carte = new Carte(50,50);
	// bib::XMLEngine::save<Carte>(*carte, "Carte", "alpha.map");

	carte = bib::XMLEngine::load < edt::Carte > ("Carte", "data/map/sf/alpha.map");
	coeff_zoom = 1;
	tt = cce::Univers::getInstance()->getTileTemplate(100000000);
	current_pays = "Mordor";
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

	list < cce::Vue * >::iterator it;
	vues.end();
	for (it = vues.begin(); it != vues.end(); it++)
	    (*it)->updateCameraPosition(x, y);
    }

    void Modele::zoom(int ticks) {
	coeff_zoom *= 1 - ticks * 0.05;
	list < cce::Vue * >::iterator it;
	for (it = vues.begin(); it != vues.end(); it++)
	    (*it)->updateCameraZoom(1 - ticks * 0.05);
    }

    void Modele::resetZoom() {
	coeff_zoom = 1;
	list < cce::Vue * >::iterator it;
	for (it = vues.begin(); it != vues.end(); it++)
	    (*it)->resetCameraZoom();
    }

    void Modele::placeTile(int x, int y) {
	getRepere()->setTile(tt, x, y);
    }

    void Modele::placeDecor(int x, int y) {
	carte->getCoucheDecor()->addDecor(dt, x, y);
    }

    void Modele::deleteTile(int x, int y) {
	getRepere()->unsetTile(x, y);
    }
    
    void Modele::addRegion(string nom)
    {
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

}