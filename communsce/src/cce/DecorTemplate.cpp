#include "cce/DecorTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce{

DecorTemplate::DecorTemplate()
{
  
}

void DecorTemplate::loadTexture()
{
  //à supprimer pour ne pas charger tous les décors en mémoire
  ImageManager::getInstance()->load_asset(id, path);
  
  texture = &ImageManager::getInstance()->get_asset(id);
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

