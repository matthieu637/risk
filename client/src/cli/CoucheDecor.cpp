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

bool CoucheDecor::collision(Unit* u, sf::Vector2f position) //optimiser avec une fonction collisionUnit (les decors sont fixes pour le pathfinding)
{
    return damier_units->collision(u, position);
}

set<Unit*>* CoucheDecor::getAllUnits()
{
    return allUnits;
}

}