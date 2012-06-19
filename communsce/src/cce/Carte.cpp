#include "cce/Carte.hpp"
#include "cce/Pays.hpp"
#include "cce/Region.hpp"

namespace cce{

Carte::Carte()
{
  
}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(repere, states);
    target.draw(couche_decor, states);
}


list<Region> Carte::getListRegions()
{
    
    list<Pays>* lp = getListPays();
    list<Region> lr;
    list<Pays>::iterator it;
    list<Region>::iterator ir;
      for (it = lp->begin(); it != lp->end(); it++)
	for(ir=(*it).getRegions().begin(); ir!=(*it).getRegions().end(); ir++)
	  lr.push_back(*ir);
  return lr;
}

}