#include "cce/DecorTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce{

DecorTemplate::DecorTemplate()
{

}

void DecorTemplate::loadAfterXML(int id)
{
  this->id = id;
  
  //à supprimer pour ne pas charger tous les décors en mémoire
  ImageManager::getInstance()->load_asset(id, path);
  
  texture = &ImageManager::getInstance()->get_asset(id);
  initAnimation(); 
}

// AnimationTemplate *DecorTemplate::getMapTemplate(){
//     return &mapAnimTemplate["moveUp"];
// }

map<std::string,AnimationTemplate> *DecorTemplate::getMapTemplate(){
    return &mapAnimTemplate;
}

void DecorTemplate::initAnimation()
{
   // Specify static subrect which is shown unless an other animation is active
  thor::FrameAnimation defaultAnim;
  defaultAnim.addFrame(1.f, sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y)); 
  // Register animations with their corresponding durations
  (*getMapTemplate())["moveUp"].getAnimathor()->setDefaultAnimation(defaultAnim, sf::seconds(1.f));
  (*getMapTemplate())["moveRight"].getAnimathor()->setDefaultAnimation(defaultAnim, sf::seconds(1.f));
  

}


DecorTemplate::~DecorTemplate()
{

}


Texture* DecorTemplate::getTexture()
{
  return texture;
}

int DecorTemplate::getID()
{
  return id;
}

bool DecorTemplate::bloquant()
{
  return bloquant_;
}

}

