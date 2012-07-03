#include "cli/Joueur.hpp"
#include "cce/Pays.hpp"
#include "cce/Region.hpp"

using namespace cli;
using cce::Pays;
using cce::Region;

Joueur::Joueur(int num, player_color couleur, int nbPlayers)
{
  player_number = num;
  color = couleur;
  income = 10;
  for(int i=0; i < nbPlayers; i++)
    if(i != player_number)
      allied_player[nbPlayers] = false;
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

int Joueur::getIncome()
{
  return income;
}

int Joueur::getGold()
{
  return gold;
}
