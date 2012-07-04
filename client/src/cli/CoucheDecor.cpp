#include "cli/CoucheDecor.hpp"
#include "cce/CoucheDecor.hpp"
#include "cli/Unit.hpp"
#include "cli/Joueur.hpp"
#include "bib/Logger.hpp"
#include <cmath>

namespace cli{

CoucheDecor::CoucheDecor() : cce::CoucheDecor()
{
}

CoucheDecor::~CoucheDecor()
{

}

void CoucheDecor::init()
{
    allUnits = new set<Unit*>();
}

void CoucheDecor::addUnit(Unit* u)
{
    addDecor(u);
    allUnits->insert(u);
}

void CoucheDecor::removeUnit(Unit* u)
{
    removeDecor(u);
    allUnits->erase(u);
}

list<Unit*> CoucheDecor::getUnitsInRect(sf::FloatRect* rectangleSelection)//FIXME set de selection pour ajout à la selection en log N
{
    list<Unit*> liste;
    set<Unit*>::iterator it;
    for(it = allUnits->begin(); it != allUnits->end(); it++)
      if(rectangleSelection->contains((*it)->getPosition().x + (*it)->getSocleCenter().x, (*it)->getPosition().y + (*it)->getSocleCenter().y)) 
	liste.push_back(*it);
    return liste;
}

Unit* CoucheDecor::getUnit(sf::Vector2f position)
{
    int a;
    set<Unit*>::reverse_iterator it;
    for(it = allUnits->rbegin(); it != allUnits->rend(); it++)
      if((*it)->getGlobalBounds().contains(position)) {
	a = (*it)->getTexture()->copyToImage().getPixel(position.x - (*it)->getPosition().x, position.y - (*it)->getPosition().y).a;
	if(a > 122) //pixel transparent? Permet de détecter véritablement le decor cliqué lorsqu'ils sont superposés
	  return *it;
      }
    return nullptr;
}

Unit* CoucheDecor::closestEnemyInRange(int range, sf::Vector2f position, Joueur* j)
{
    Unit* u = nullptr;
    int sizeRect = range*2;
    sf::FloatRect rect = sf::FloatRect(position, sf::Vector2f(sizeRect, sizeRect));
    list<Unit*> liste = getUnitsInRect(&rect);
    
    if(liste.empty())
      return nullptr;
    
    float distance_actuelle = 500, new_distance;
    list<Unit*>::iterator it;
    sf::Vector2f distance;
    
    for(it = liste.begin(); it != liste.end(); it++){
      if(j->isAllied((*it)->getOwner()->getNumber()) || (*it)->isDead()) // joueur allié (ou soi) ou unité morte
	continue;
      
      distance = position - (*it)->getPosition();
      new_distance = sqrt(distance.x * distance.x + distance.y * distance.y);
      
      if(new_distance > range) // hors de portée
	continue;
      
      if(new_distance < distance_actuelle){ // unité plus proche
	  u = *it;
	  distance_actuelle = new_distance;
      }
    }
    return u;
}

bool CoucheDecor::collision(cce::Decor* d, sf::Vector2f position) //optimiser avec une fonction collisionUnit (les decors sont fixes pour le pathfinding)
{
    sf::Vector2f distance;
    float d_rad = d->getSelectionCircle()->getRadius();
    float it_rad;
    
    set<cce::Decor*>::iterator it;
    for(it = decors.begin(); it != decors.end(); it++) {
      distance = position - (*it)->getSocleCenterGlobal();
      it_rad = (*it)->getSelectionCircle()->getRadius();
      if(sqrt(distance.x * distance.x + distance.y * distance.y) < d_rad + it_rad)
	return true;
    }
    return false;
}

set<Unit*>* CoucheDecor::getAllUnits()
{
    return allUnits;
}

}