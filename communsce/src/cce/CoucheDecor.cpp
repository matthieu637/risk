#include "cce/CoucheDecor.hpp"
#include "cce/Decor.hpp"
#include "cce/DecorTemplate.hpp"
#include "bib/Logger.hpp"

namespace cce{

CoucheDecor::CoucheDecor()
{
    decors = new set<Decor>;
}

CoucheDecor::~CoucheDecor()
{

}

const Decor* CoucheDecor::getDecor(int x, int y)
{
    int a;
    set<Decor>::reverse_iterator rit;
    for(rit = decors->rbegin(); rit != decors->rend(); rit++){
	if(rit->getGlobalBounds().contains(x, y)){
	    a = rit->getTexture()->copyToImage().getPixel(x - rit->getPosition().x, y - rit->getPosition().y).a;
	    if(a != 0) //pixel transparent? Permet de détecter véritablement le decor cliqué lorsqu'ils sont superposés
		return &(*rit);
	}
	else if(y > rit->getPosition().y + rit->getGlobalBounds().top)
	    return nullptr;
    }
    return nullptr;
}

void CoucheDecor::setDecorMove(int x, int y){
    d_move = getDecor(x, y);
}

void CoucheDecor::moveDecor(int dx, int dy)
{
    if(d_move == nullptr)
      return;
    int ancien_x = d_move->getPosition().x;
    int ancien_y = d_move->getPosition().y;
    int nouveau_x = ancien_x + dx;
    int nouveau_y = ancien_y + dy;
    DecorTemplate *dt = d_move->getTemplate();
    Decor* d_new = new Decor(dt, nouveau_x, nouveau_y);
    if((&(*(decors->find(*d_new))))->getPosition() != d_new->getPosition()){
      decors->erase(*d_move);
      decors->insert(*d_new);
      d_move = d_new;
    }
}

void CoucheDecor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    set<Decor>::iterator it = decors->begin();
    for(; it != decors->end(); ++it)
      target.draw(*it, states);
}

void CoucheDecor::addDecor(DecorTemplate *dt, int x, int y)
{
    decors->insert(Decor(dt, x - dt->getTexture()->getSize().x/2, y - dt->getTexture()->getSize().y * 3/4));
}


void CoucheDecor::removeDecor(int x, int y)
{
    const Decor *d = getDecor(x,y);
    if(d != nullptr)
      decors->erase(*d);
}

}