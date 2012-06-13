#include "cce/Carte.hpp"

#include "bib/XMLEngine.hpp"

using namespace cce;


Carte::Carte():repere()
{
  
}

Carte::Carte(int x, int y):repere(x,y)
{
  
}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(repere, states);
}



