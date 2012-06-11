#include "cce/TileTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce{

TileTemplate::TileTemplate()
{
  
}

void TileTemplate::init(int _id, bool _bloquante, string _path)
{
  //à supprimer pour ne pas charger toutes les tiles en mémoire
  ImageManager::getInstance()->load_asset(_id, _path);
  
  id = _id;
  path = _path;
  bloquante_ = _bloquante;
  texture = &ImageManager::getInstance()->get_asset(_id);
  decalage_hauteur_image = (texture->getSize().y - hauteurTile);
}

TileTemplate::~TileTemplate()
{

}

Texture* TileTemplate::getTexture()
{
  return texture;
}

int TileTemplate::getID()
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