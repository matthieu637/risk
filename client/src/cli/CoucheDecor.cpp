#include "cli/CoucheDecor.hpp"
#include "cce/CoucheDecor.hpp"
#include "cli/Unit.hpp"
#include "bib/Logger.hpp"

namespace cli{

CoucheDecor::CoucheDecor() : cce::CoucheDecor()
{
}

CoucheDecor::~CoucheDecor()
{

}

void CoucheDecor::addUnit(Unit* u)
{
    addDecor(u);
    allUnits.insert(u);
}

void CoucheDecor::removeUnit(Unit* u)
{
    removeDecor(u);
    allUnits.erase(u);
}

list<Unit*> CoucheDecor::getUnitsInRect(sf::RectangleShape* rectangleSelection)
{
    list<Unit*> liste;
    set<Unit*>::iterator it;
    for(it = allUnits.begin(); it != allUnits.end(); it++)
      if(rectangleSelection->getGlobalBounds().contains((*it)->getPosition().x + (*it)->getSocle().x, (*it)->getPosition().y + (*it)->getSocle().y)) 
	liste.push_back(*it);
    return liste;
}

set<Unit*>* CoucheDecor::getAllUnits()
{
    return &allUnits;
}

}