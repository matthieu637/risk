#include "cce/Modele.hpp"
#include "cce/Vue.hpp"
#include "cce/Univers.hpp"
#include "bib/XMLEngine.hpp"

using cce::Modele;
using std::vector;

namespace cce{

Modele::Modele()
{
 // carte = new Carte(50,50);
 // bib::XMLEngine::save<Carte>(*carte, "Carte", "alpha.map");
  carte = bib::XMLEngine::load<Carte>("Carte", "data/map/sf/alpha.map");
  coeff_zoom = 1;
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
    target.draw(*carte,states);
}

void Modele::setCamOrigine(int cameraX, int cameraY)
{
    cameraOrigineX = cameraX,
    cameraOrigineY = cameraY;
}

void Modele::moveView(int dx, int dy, int cameraX, int cameraY, int cameraL, int cameraH)
{
    int x = cameraOrigineX + dx * coeff_zoom;
    int y = cameraOrigineY + dy * coeff_zoom;
    int x_max = carte->getRepere()->getLargeur() * 158;
    int y_max = carte->getRepere()->getHauteur() * 44;
    
    if((x < 0 && cameraX < 0) || (x > x_max && cameraX > x_max))
	x = cameraX;
    if((y < 0 && cameraY < 0) || (y > y_max && cameraY > y_max))
	y = cameraY;
    
    vector<Vue>::iterator it;
    for (it=vues.begin() ; it < vues.end(); it++)
	it->updateCameraPosition(x, y);
}

void Modele::zoom(int ticks)
{
    coeff_zoom *= 1 - ticks * 0.05;
    vector<Vue>::iterator it;
    for (it=vues.begin() ; it < vues.end(); it++)
	it->updateCameraZoom(1 - ticks * 0.05);
}

void Modele::resetZoom()
{
    coeff_zoom = 1;
    vector<Vue>::iterator it;
    for (it=vues.begin() ; it < vues.end(); it++)
	it->resetCameraZoom();
}

}
