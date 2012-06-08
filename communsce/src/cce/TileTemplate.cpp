#include "cce/TileTemplate.hpp"

namespace cce{

TileTemplate::TileTemplate(int _id, bool _bloquante, Texture *_texture)
{
  id = _id;
  bloquante = _bloquante;
  texture = _texture;
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

bool TileTemplate::bloquante()
{
  return bloquante;
}

}