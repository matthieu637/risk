#include "cce/TileTemplate.hpp"

namespace cce{

TileTemplate::TileTemplate(int _id, bool _bloquante, Texture *_texture)
{
  id = _id;
  bloquante_ = _bloquante;
  texture = _texture;
  decalage_hauteur_image = (_texture->getSize().y - hauteurTile);
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