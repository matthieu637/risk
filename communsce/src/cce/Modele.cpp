#include "cce/Modele.hpp"

using cce::Modele;

Modele::Modele()
{

}

void Modele::update()
{
  
}

void Modele::saveCarte(const std::string& chemin)
{
  (void)chemin;
}

void Modele::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(carte,states);
}