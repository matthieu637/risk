#include "cli/CoucheDecor.hpp"
#include "cce/CoucheDecor.hpp"
#include "cli/Unit.hpp"
#include "cli/Damier.hpp"
#include "bib/Logger.hpp"
#include <cmath>

namespace cli{

CoucheDecor::CoucheDecor() : cce::CoucheDecor()
{
}

CoucheDecor::~CoucheDecor()
{

}

void CoucheDecor::init(int largeurRepere, int hauteurRepere)
{
    allUnits = new set<Unit*>();
    damier_units = new Damier(largeurRepere, hauteurRepere);
}

void CoucheDecor::addUnit(Unit* u)
{
    addDecor(u);
    allUnits->insert(u);
    damier_units->addUnit(u);
}

void CoucheDecor::removeUnit(Unit* u)
{
    removeDecor(u);
    allUnits->erase(u);
    damier_units->removeUnit(u);
}

Unit* CoucheDecor::getUnit(sf::Vector2f position)
{
    return damier_units->getUnit(position);
}

list<Unit*> CoucheDecor::getUnitsInRect(sf::FloatRect* rectangleSelection)
{
    return damier_units->getUnitsInRect(rectangleSelection);
}

Unit* CoucheDecor::closestEnemyInRange(int range, sf::Vector2f position, Joueur* j)
{
    return damier_units->closestEnemyInRange(range, position, j);
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