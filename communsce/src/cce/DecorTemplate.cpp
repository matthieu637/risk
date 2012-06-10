#include "cce/DecorTemplate.hpp"

namespace cce{

DecorTemplate::DecorTemplate(int _id, bool _bloquant, Texture *_texture)
{
  id = _id;
  bloquant_ = _bloquant;
  texture = _texture;
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

