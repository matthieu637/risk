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
      if(rectangleSelection->getGlobalBounds().contains((*it)->getPosition().x + (*it)->getSocleCenter().x, (*it)->getPosition().y + (*it)->getSocleCenter().y)) 
	liste.push_back(*it);
    return liste;
}

Unit* CoucheDecor::getUnit(sf::Vector2f position)
{
    int a;
    list<Unit*>::iterator it;
    for(it = allUnits->begin(); it != allUnits->end(); it++)
        if((*it)->getGlobalBounds().contains(position)) {
            a = (*it)->getTexture()->copyToImage().getPixel(position.x - (*it)->getPosition().x, position.y - (*it)->getPosition().y).a;
            if(a > 122) //pixel transparent? Permet de détecter véritablement le decor cliqué lorsqu'ils sont superposés
                return *it;
        }
    return nullptr;
}

list<Unit*>* CoucheDecor::getAllUnits()
{
    return allUnits;
}

}