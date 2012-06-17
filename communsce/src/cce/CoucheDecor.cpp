#include "cce/CoucheDecor.hpp"
#include "cce/Decor.hpp"

namespace cce{

CoucheDecor::CoucheDecor()
{
  decors = new std::set<Decor>;
}

CoucheDecor::~CoucheDecor()
{

}

const Decor* CoucheDecor::getDecor(int x, int y)
{
  int a;
  std::set<Decor>::iterator it = decors->begin();
  for(; it != decors->end(); it++){
      if(it->getGlobalBounds().contains(x, y)){
	  a = it->getTexture()->copyToImage().getPixel(x - it->getPosition().x, y - it->getPosition().y).a;
	  if(a != 0) //pixel transparent? Permet de détecter véritablement le decor cliqué lorsqu'ils sont superposés
	      return &(*it);
      }
      else if(it->getPosition().y > y)
	  return NULL;
  }
  return NULL;
}


void CoucheDecor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  std::set<Decor>::iterator it = decors->begin();
  for(; it != decors->end(); ++it)
    target.draw(*it, states);
}

void CoucheDecor::addDecor(DecorTemplate *dt, int x, int y)
{
  decors->insert(Decor(dt, x, y));
}


void CoucheDecor::removeDecor(int x, int y)
{
  decors->erase(*getDecor(x, y));
}

}