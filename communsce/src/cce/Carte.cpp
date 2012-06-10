#include "cce/Carte.hpp"

using namespace cce;


Carte::Carte():repere(50,50)
{

}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(repere, states);
}



