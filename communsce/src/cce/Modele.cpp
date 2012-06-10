#include "cce/Modele.hpp"

using cce::Modele;

Modele::Modele()
{

}

void Modele::update()
{
  
}

void Modele::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(carte,states);
}