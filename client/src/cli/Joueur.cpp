#include "cli/Joueur.hpp"
#include "cce/Pays.hpp"
#include "cce/Region.hpp"
#include "cli/Unit.hpp"

using namespace cli;
using cce::Pays;
using cce::Region;

Joueur::Joueur()
{
  
}

Joueur::Joueur(int num, player_color couleur, int nbPlayers)
{
  player_number = num;
  color = couleur;
  income = 10;
  
  allied_player = vector<bool>(nbPlayers+1);
  allied_player[player_number] = true; //allié à soi-même
}

Joueur::~Joueur()
{
  
}

void Joueur::addPays(Pays* p)
{
  income += p->getIncome();
  pays_controles.push_back(p);
}

void Joueur::addRegion(Region* r)
{
  income += r->getIncome();
  regions_controles.push_back(r);
}

void Joueur::removePays(Pays* p)
{
  income -= p->getIncome();
  pays_controles.remove(p);
}

void Joueur::removeRegion(Region* r)
{
  income -= r->getIncome();
  regions_controles.remove(r);
}

void Joueur::addUnit(Unit* u)
{
  units.push_back(u);
}

void Joueur::removeUnit(Unit* u)
{
  units.remove(u);
}

void Joueur::setAllied(int num_joueur, bool allied)
{
  if(num_joueur != player_number)
    allied_player[num_joueur] = allied;
}

bool Joueur::isAllied(int num_joueur)
{
  return allied_player[num_joueur];
}

list<Region*> Joueur::getRegions()
{
  return regions_controles;
}

list<Pays*> Joueur::getPays()
{
  return pays_controles;
}

int Joueur::getNumber()
{
  return player_number;
}

int Joueur::getIncome()
{
  return income;
}

int Joueur::getGold()
{
  return gold;
}

list<Unit*> Joueur::getUnitsInRect(sf::FloatRect rectangleSelection)
{
    list<Unit*> liste;
    list<Unit*>::iterator it;
    for(it = units.begin(); it != units.end(); it++)
      if(rectangleSelection.contains((*it)->getPosition().x + (*it)->getSocleCenter().x, (*it)->getPosition().y + (*it)->getSocleCenter().y)) 
	liste.push_back(*it);
    return liste;
}
