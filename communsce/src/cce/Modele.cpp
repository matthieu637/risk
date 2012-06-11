#include "cce/Modele.hpp"
#include "cce/Univers.hpp"
#include "bib/XMLEngine.hpp"

using cce::Modele;

Modele::Modele()
{
  univ = bib::XMLEngine::load<Univers>("Univers", "data/sf.univ");
}

Modele::~Modele()
{
  delete univ;
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