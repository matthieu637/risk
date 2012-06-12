#include "cce/TileTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce{

TileTemplate::TileTemplate():id(0)
{
  
}

void TileTemplate::loadAfterXML(int id)
{
  //à supprimer pour ne pas charger toutes les tiles en mémoire
  ImageManager::getInstance()->load_asset(id, path);
  
  texture = &ImageManager::getInstance()->get_asset(id);
  decalage_hauteur_image = (texture->getSize().y - hauteurTile);
}

TileTemplate::~TileTemplate()
{

}

Texture* TileTemplate::getTexture()
{
  return texture;
}

int TileTemplate::getID() const
{
  return id;
}

int TileTemplate::getDecalageHauteur()
{
  return decalage_hauteur_image;
}

bool TileTemplate::bloquante()
{
  return bloquante_;
}

}