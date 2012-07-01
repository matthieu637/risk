#include "cli/Modele.hpp"
#include "cli/Vue.hpp"
#include "cli/Unit.hpp"
#include "cce/Tile.hpp"
#include "cli/Carte.hpp"
#include "cce/Repere.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/ImageManager.hpp"
#include <list>
#include <set>
#include <string>
#include <CEGUI/CEGUI.h>
#include "cli/CoucheDecor.hpp"
#include "cce/CoucheDecor.hpp"

using std::list;
using std::set;
using std::string;

namespace cli {

Modele::Modele():cce::Modele()
{
    carte = bib::XMLEngine::load <cli::Carte>("Carte", "data/map/sf/alpha.map");
    // carte = new Carte; FIXME
    getCoucheDecor()->init();
    
    coeff_zoom = 1;
    
    spawnUnit(300000000,150,150);
    
    //parametres du rectangle de selection
    rectangleSelection = new sf::RectangleShape();
    rectangleSelection->setOutlineColor(sf::Color(0,150,0,255));
    rectangleSelection->setOutlineThickness(1);
    rectangleSelection->setFillColor(sf::Color(0,150,0,50));
    selectionBool = false;
}

Modele::~Modele() {

}

void Modele::update()
{
    cce::Modele::update();
    list<Unit*>::iterator it;
    list<Unit*>* allunits = getCoucheDecor()->getAllUnits();
    for(it = allunits->begin(); it !=  allunits->end(); ++it){
 	getCoucheDecor()->removeDecor(*it);
 	(*it)->applyOrder();
 	getCoucheDecor()->addDecor(*it);
    }
}

void Modele::spawnUnit(int id, int x, int y)
{
    Unit* u = new Unit;
    u->setId(id);
    u->setPosition(x,y);
    getCoucheDecor()->addUnit(u);
}

void Modele::setCamOrigine(int cameraX, int cameraY)
{
    cameraOrigineX = cameraX;
    cameraOrigineY = cameraY;
}

void Modele::moveView(int dx, int dy, int cameraL, int cameraH)
{
    int x = cameraOrigineX + dx * coeff_zoom;
    int y = cameraOrigineY + dy * coeff_zoom;
    int x_min = cce::Repere::l_tile_demi + cameraL/2;
    int y_min = cce::Repere::h_tile_demi + cameraH/2;
    int x_max = carte->getRepere()->largeur_pixels - x_min;
    int y_max = carte->getRepere()->hauteur_pixels - y_min;

    if (x < x_min)
      x = x_min;
    if (x > x_max)
      x = x_max;
    if (y < y_min)
      y = y_min;
    if (y > y_max)
      y = y_max;

    for(it = vues.begin(); it != vues.end(); it++)
      (*it)->updateCameraPosition(x, y);
}

void Modele::zoom(int ticks)
{
    coeff_zoom *= 1 - ticks * 0.05;
    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)*it)->updateCameraZoom(1 - ticks * 0.05);
}

void Modele::resetZoom()
{
    coeff_zoom = 1;
    for (it = vues.begin(); it != vues.end(); it++)
        (*it)->resetCameraZoom();
}

void Modele::windowResized(int width, int height)
{
    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)(*it))->updateSize(width, height);
    resetZoom();
}

void Modele::moveUnitSelection(sf::Vector2i mousePosition)
{
    list<Unit*>::iterator it;
    for(it = selectionUnits.begin(); it != selectionUnits.end(); ++it)
	(*it)->orderMove(mousePosition);
}

void Modele::initSelection(int x, int y)
{
    rectangleSelection->setSize(sf::Vector2f(0,0));
    origineSelection = sf::Vector2f(x, y);
    rectangleSelection->setPosition(origineSelection);
    selectionBool = true;
}

void Modele::moveSelection(int x, int y)
{
    sf::Vector2f sizeSelection = sf::Vector2f(abs(origineSelection.x - x),abs(origineSelection.y - y));
    rectangleSelection->setSize(sizeSelection);
    
    //tests des différents cas de drag : on change l'origine du rectangle
    if(origineSelection.x < x) //Drag vers la droite
	if(origineSelection.y < y) //Drag vers bas droite
	    ;//pas de changement d'origine dans ce cas
	else //Drag vers haut droite
	    rectangleSelection->setPosition(origineSelection.x,y);
    
    else //Drag vers la gauche
	if(origineSelection.y < y) //Drag vers bas gauche
	    rectangleSelection->setPosition(x,origineSelection.y);
	else //Drag vers haut gauche
	    rectangleSelection->setPosition(x,y);
}

void Modele::endSelection()
{
    selectionBool = false;
    list<Unit*> units_in_rect = getCoucheDecor()->getUnitsInRect(rectangleSelection);
    if(!units_in_rect.empty())
      selectionUnits = units_in_rect;
}

void Modele::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    cce::Modele::draw(target, states);
    if(selectionBool) {
       target.draw(*rectangleSelection, states);
   }
}
  
}
