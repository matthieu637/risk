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
#include "cli/Joueur.hpp"

using std::list;
using std::set;
using std::string;

namespace cli {

Modele::Modele():cce::Modele()
{
    carte = bib::XMLEngine::load <cli::Carte>("Carte", "data/map/sf/alpha.map");
    // carte = new Carte; FIXME
    getCoucheDecor()->init(carte->getRepere()->largeur_pixels, carte->getRepere()->hauteur_pixels);
    
    coeff_zoom = 1;

    //parametres du rectangle de selection
    rectangleSelection = new sf::RectangleShape();
    rectangleSelection->setOutlineColor(sf::Color(0,150,0,255));
    rectangleSelection->setOutlineThickness(1);
    rectangleSelection->setFillColor(sf::Color(0,150,0,50));
    selectionBool = false;
    
    //joueurs
    player_number = 1;
    int nbJoueurs = 2;
    
    players = vector<Joueur>(nbJoueurs+1);
    
    for(int i=1; i<=nbJoueurs; i++)
      players[i] = Joueur(i, player_color::rouge, nbJoueurs);
}

Modele::~Modele() {

}

void Modele::update()
{
    cce::Modele::update();
    set<Unit*>::iterator it;
    set<Unit*> allunits = *getCoucheDecor()->getAllUnits();
    for(it = allunits.begin(); it !=  allunits.end(); ++it)
      if((*it) != nullptr)
	(*it)->applyOrder();
    //detruire les unités mortes
    for(it = getCoucheDecor()->getAllUnits()->begin(); it !=  getCoucheDecor()->getAllUnits()->end(); ++it)
      if((*it) != nullptr && (*it)->isDead())
	deleteUnit(*it);
}

void Modele::spawnUnit(int id, int x, int y, int joueur)
{
    Unit* u = new Unit(this, &players[joueur]);
    u->setId(id);
    u->setPosition(x,y);
    u->animate();
    getCoucheDecor()->addUnit(u);
    players[joueur].addUnit(u);
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
    float coeff_ajout = 1 - ticks * 0.05;
    float coeff_new = coeff_zoom * coeff_ajout;
    
    if(coeff_new < 0.75 || coeff_new > 1.5)
      return;
    
    coeff_zoom = coeff_new;
    for (it = vues.begin(); it != vues.end(); it++)
        ((Vue*)*it)->updateCameraZoom(coeff_ajout);
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
    set<Unit*>::iterator it;
    //si on clique sur un décor, on le suit
    Unit* to_follow = getCoucheDecor()->getUnit(sf::Vector2f(mousePosition));
    if(to_follow != nullptr)
      
      for(it = selectionUnits.begin(); it != selectionUnits.end(); ++it)
	(*it)->orderFollow(to_follow);
    //sinon on bouge au point cliqué
    else
      for(it = selectionUnits.begin(); it != selectionUnits.end(); ++it)
	(*it)->orderMove(mousePosition);
}

void Modele::on_attack(sf::Vector2i mousePosition)
{
    Unit* to_attack = getCoucheDecor()->getUnit(sf::Vector2f(mousePosition));
    
    if(to_attack != nullptr && to_attack->getOwner()->getNumber() != player_number){
      set<Unit*>::iterator it;
      for(it = selectionUnits.begin(); it != selectionUnits.end(); ++it)
	(*it)->orderAttack(to_attack);
    }
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

    list<Unit*> units_in_rect = players[player_number].getUnitsInRect(rectangleSelection->getGlobalBounds());
    if(!units_in_rect.empty())
      selectionUnits.clear();
      list<Unit*>::const_iterator it;
      for(it = units_in_rect.begin(); it != units_in_rect.end(); ++it){
	this->addUnitSelection(*it);
      }
}


void Modele::endSelectionShift(){
    selectionBool = false;
    list<Unit*> units_in_rect =  players[player_number].getUnitsInRect(rectangleSelection->getGlobalBounds());
    if(!units_in_rect.empty()){
     // LOG_DEBUG("test selectunitssizebefore : " << selectionUnits.size());
      list<Unit*>::const_iterator it;
      for(it = units_in_rect.begin(); it != units_in_rect.end(); ++it){
	this->addUnitSelection(*it);
      }
     // LOG_DEBUG("test selectunitssizeafter : " << selectionUnits.size());      
    }
}

void Modele::removeSelection(int x, int y){
    selectionBool = false;
    sf::Vector2f i = sf::Vector2f(x, y);
    Unit* u = this->getCoucheDecor()->getUnit(i);
    if(u!=nullptr){
      this->removeUnitSelection(u);
    }
}

Unit* Modele::closestEnemyInRange(int range, sf::Vector2f position, Joueur* j)
{
    return getCoucheDecor()->closestEnemyInRange(range, position, j);
}

void Modele::deleteUnit(Unit* u)
{
    getCoucheDecor()->removeUnit(u);
    u->getOwner()->removeUnit(u);
    this->removeUnitSelection(u);
    delete u;
}

void Modele::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Rendu du repere
    target.draw(*carte->getRepere(), states);
    //Rendu des cercles de sélection
    set<Unit*>::const_iterator it;
    for(it = selectionUnits.begin(); it != selectionUnits.end(); ++it){
 	target.draw(*(*it)->getSelectionCircle());
    }
    //Rendu des décors
    target.draw(*carte->getCoucheDecor(), states);
    //Rendu du rectangle de selection
    if(selectionBool){
       target.draw(*rectangleSelection, states);
    }
}
  
  void Modele::addUnitSelection(Unit* un){
    selectionUnits.insert(un);
  }
  
  void Modele::removeUnitSelection(Unit* un){
    selectionUnits.erase(un);
  }
  
}
