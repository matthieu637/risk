#include "cce/Modele.hpp"
#include "cce/Vue.hpp"
#include "cce/Univers.hpp"
#include "bib/XMLEngine.hpp"

using cce::Modele;
using std::vector;

namespace cce{

Modele::Modele()
{

}

Modele::~Modele()
{
  
}

void Modele::update()
{
  
}

void Modele::addVue(Vue* vue)
{
  vues.push_back(*vue);
}

void Modele::saveCarte(const std::string& chemin)
{
  (void)chemin;
}

void Modele::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(carte,states);
}

void Modele::moveView(int dx, int dy, int cameraX, int cameraY, int cameraL, int cameraH)
{
    if(cameraX + dx < cameraL/2)
	dx = 0;
    else if(cameraX + dx > carte.getRepere()->getLargeur() - cameraL/2 + 88)
	dx = 0;

    if(cameraY + dy < cameraH/2)
	dy = 0;
    else if(cameraY + dy > carte.getRepere()->getHauteur() - cameraH/2 + 44)
	dy = 0;
    
    cameraX += dx;
    cameraY += dy;
    
    vector<Vue>::iterator it;
    for (it=vues.begin() ; it < vues.end(); it++)
	it->updateCamera(cameraX, cameraY);
}

}
