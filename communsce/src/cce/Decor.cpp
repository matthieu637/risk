#include "cce/Decor.hpp"
#include "cce/DecorTemplate.hpp"

using namespace std;

namespace cce{

Decor::Decor(DecorTemplate *_dt, int x, int y) : Sprite()
{
  dt = _dt;
  setPosition(x,y);
  setTexture(dt->getTexture());
}

Decor::~Decor()
{
    
}

DecorTemplate* Decor::getTemplate() const
{
    return dt;
}

void Decor::setTexture(Texture* texture)
{
    Sprite::setTexture(*texture, true);
    yCompare = getPosition().y * 2 + getGlobalBounds().height;
}

bool Decor::inferieurA(const Decor &d) const
{
    bool meme_hauteur = yCompare == d.yCompare;
    if(meme_hauteur)
	return getPosition().x < d.getPosition().x;
    else
      return meme_hauteur;
}

bool operator<(Decor const &d1, Decor const &d2)
{
  if(d1.inferieurA(d2))
    return true;
  else
    return false;
}

}