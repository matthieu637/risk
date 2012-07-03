#include "cli/CoucheDecor.hpp"
#include "cce/CoucheDecor.hpp"
#include "cli/Unit.hpp"
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

list<Unit*> CoucheDecor::getUnitsInRect(sf::RectangleShape* rectangleSelection)
{
    list<Unit*> liste;
    set<Unit*>::iterator it;
    for(it = allUnits->begin(); it != allUnits->end(); it++)
      if(rectangleSelection->getGlobalBounds().contains((*it)->getPosition().x + (*it)->getSocleCenter().x, (*it)->getPosition().y + (*it)->getSocleCenter().y)) 
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