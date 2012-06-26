#include "cce/Modele.hpp"
#include "cce/Vue.hpp"
#include "cce/Univers.hpp"
#include "cce/ImageManager.hpp"
#include <cce/Console.hpp>
#include "bib/XMLEngine.hpp"
#include <fstream>
#include <iostream>

using std::vector;

namespace cce{

Modele::Modele()
{
    cce::ImageManager::getInstance();
    cce::Univers::getInstance();
    cce::Univers::getInstance()->init();

}

Modele::~Modele()
{
  
}

void Modele::update()
{
  
}

CEGUI::String Modele::openCarte(CEGUI::String chemin) {
    LOG_DEBUG("modele->openCarte->chemin "+chemin);
    ifstream fichier(chemin.c_str(), std::ios::in);
    if(fichier){  
	  carte =  bib::XMLEngine::load<cce::Carte>("CARTE",chemin.c_str());
	  return "La carte "+chemin+" a bien été chargée";
    }else{
	  return "La carte "+chemin+" n'existe pas";
    }
    fichier.close();
}

void Modele::addVue(Vue* vue)
{
  vues.push_back(vue);
}

void Modele::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*carte,states);
}

Carte* Modele::getCarte() 
{
  return carte;
}

}
