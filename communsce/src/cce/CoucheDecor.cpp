#include "cce/CoucheDecor.hpp"

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


void CoucheDecor::dessiner(RenderTarget& cible)
{
  std::set<Decor>::iterator it = decors->begin();
  for(; it != decors->end(); ++it)
    cible.draw(*it);
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