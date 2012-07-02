#include "cli/Joueur.hpp"
#include "cce/Pays.hpp"
#include "cce/Region.hpp"

using namespace cli;
using cce::Pays;
using cce::Region;

Joueur::Joueur(int num, player_color couleur)
{
  player_number = num;
  color = couleur;
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

list<Region*> Joueur::getRegions()
{
  return regions_controles;
}

list<Pays*> Joueur::getPays()
{
  return pays_controles;
}

int Joueur::getIncome()
{
  return income;
}

int Joueur::getGold()
{
  return gold;
}
