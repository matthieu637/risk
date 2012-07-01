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

void CoucheDecor::init()
{
    allUnits = new list<Unit*>();
}

void CoucheDecor::addUnit(Unit* u)
{
    addDecor(u);
    allUnits->push_back(u);
}

void CoucheDecor::removeUnit(Unit* u)
{
    removeDecor(u);
    allUnits->remove(u);
}

list<Unit*> CoucheDecor::getUnitsInRect(sf::RectangleShape* rectangleSelection)
{
    list<Unit*> liste;
    list<Unit*>::iterator it;
    for(it = allUnits->begin(); it != allUnits->end(); it++)
      if(rectangleSelection->getGlobalBounds().contains((*it)->getPosition().x + (*it)->getSocle().x, (*it)->getPosition().y + (*it)->getSocle().y)) 
	liste.push_back(*it);
    return liste;
}

list<Unit*>* CoucheDecor::getAllUnits()
{
    return allUnits;
}

}