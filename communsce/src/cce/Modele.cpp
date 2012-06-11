#include "cce/Modele.hpp"
#include "cce/MoteurSFML.hpp"

using cce::Modele;

Modele::Modele()
{
    
}

void Modele::init(MoteurSFML* engine)
{
    this->engine = engine;
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

void Modele::moveView(int dx, int dy)
{
    int centreX = engine->getView()->getCenter().x;
    int centreY = engine->getView()->getCenter().y;
    int largeur = engine->getView()->getSize().x;
    int hauteur = engine->getView()->getSize().y;
    
    if(centreX + dx < largeur/2)
	dx = 0;
    else if(centreX + dx > carte.getRepere()->getLargeur()*158 - largeur/2 + 88)
	dx = 0;

    if(centreY + dy < hauteur/2)
	dy = 0;
    else if(centreY + dy > carte.getRepere()->getHauteur()*44 - hauteur/2 + 44)
	dy = 0;

    engine->getView()->setCenter(centreX + dx, centreY + dy);
}