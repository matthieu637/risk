#include "cce/Carte.hpp"

namespace cce{

Carte::Carte()
{
  
}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(repere, states);
    target.draw(couche_decor, states);
}

}