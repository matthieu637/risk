#include "cce/Modele.hpp"
#include "cce/Vue.hpp"
#include "cce/Univers.hpp"
#include "cce/ImageManager.hpp"

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

void Modele::addVue(Vue* vue)
{
  vues.push_back(vue);
}

void Modele::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*carte,states);
}

}
