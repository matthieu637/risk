#include "cce/Carte.hpp"

using namespace cce;


Carte::Carte()
{
  
}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(repere, states);
}



