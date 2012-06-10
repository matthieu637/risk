#include "cce/Carte.hpp"

using namespace cce;


Carte::Carte():repere(5,8)
{

}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(repere, states);
}
