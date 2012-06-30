#include "cce/Decor.hpp"
#include "cce/DecorTemplate.hpp"
#include "bib/Logger.hpp"

using namespace std;

namespace cce{

Decor::Decor(DecorTemplate *_dt, int x, int y) : Sprite()
{
  dt = _dt;
  setPosition(x,y);
  setTexture(dt->getTexture());
  animation = dt->getAnimation();
}

Decor::Decor()
{
  dt = nullptr;
}

Decor::~Decor()
{
    
}

void Decor::animate(){  
  // Update animator and apply current animation state to the sprite
  animation.update(frameClock.restart());
  animation.animate(*this);
}

DecorTemplate* Decor::getTemplate() const
{
    return dt;
}

void Decor::setTexture(Texture* texture)
{
    Sprite::setTexture(*texture, true);
    yCompare = getPosition().y * 1.5 + getGlobalBounds().height;
}

void Decor::move(float offsetX, float offsetY)
{
    Sprite::move(offsetX, offsetY);
    yCompare = getPosition().y * 1.5 + getGlobalBounds().height;
}

bool Decor::inferieurA(const Decor &d) const
{
    if(yCompare < d.yCompare)
	return true;
    else if(yCompare == d.yCompare)
	return getPosition().x < d.getPosition().x;
    return false;
}

bool operator<(Decor const &d1, Decor const &d2)
{
    return d1.inferieurA(d2);
}

void Decor::unpause(){
  frameClock.restart();
  
}
  

}