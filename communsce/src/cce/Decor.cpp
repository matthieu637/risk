#include "cce/Decor.hpp"
#include "cce/DecorTemplate.hpp"

namespace cce{

Decor::Decor(DecorTemplate *_dt, int x, int y) : Sprite()
{
  dt = _dt;
  setPosition(x,y);
  setTexture(*(dt->getTexture()));
}

Decor::~Decor()
{
    
}

DecorTemplate* Decor::getTemplate() const
{
  return dt;
}

void Decor::setTexture(const Texture& texture, bool resetRect)
{
  Sprite::setTexture(texture, resetRect);
  yCompare = getPosition().y * 2 + getGlobalBounds().height;
}

bool operator <(Decor &d1, Decor &d2)
{
  bool meme_hauteur = d1.yCompare == d2.yCompare;
  if(meme_hauteur)
    return d1.getPosition().x < d2.getPosition().x;
  else
    return meme_hauteur;
}

}