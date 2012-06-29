#include "cce/CoucheDecor.hpp"
#include "cce/Decor.hpp"
#include "cce/DecorTemplate.hpp"
#include "cce/UnitTemplate.hpp"
#include "bib/Logger.hpp"

namespace cce{

CoucheDecor::CoucheDecor()
{
}

CoucheDecor::~CoucheDecor()
{

}

const Decor* CoucheDecor::getDecor(int x, int y)
{
    int a;
    set<Decor>::reverse_iterator rit;
    for(rit = decors.rbegin(); rit != decors.rend(); rit++){
	if(rit->getGlobalBounds().contains(x, y)){
	    a = rit->getTexture()->copyToImage().getPixel(x - rit->getPosition().x, y - rit->getPosition().y).a;
	    if(a > 122) //pixel transparent? Permet de détecter véritablement le decor cliqué lorsqu'ils sont superposés
		return &(*rit);
	}
    }
    return nullptr;
}

void CoucheDecor::setDecorMove(int x, int y){
    d_move = Decor();
    const Decor* d = getDecor(x, y);
    if(d != nullptr)
	d_move = (Decor)*d;
}

void CoucheDecor::moveDecor(int dx, int dy)
{
    if(&d_move == nullptr)
	return;
    decors.erase(d_move);
    d_move.move(dx, dy);
    if(decors.count(d_move) > 0)
	d_move.move(-dx, -dy);
    decors.insert(d_move);
}

void CoucheDecor::update()
{
    set<Decor>::iterator it = decors.begin();
    for(; it != decors.end(); ++it){
      cce::Decor dd = *it;
      dd.animate();
    }
      //((Decor*)&(*it))->animate();
}

void CoucheDecor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    set<Decor>::iterator it = decors.begin();
    for(; it != decors.end(); ++it)
      target.draw(*it, states);
}

void CoucheDecor::addDecor(DecorTemplate *dt, int x, int y)
{
    decors.insert(Decor(dt, x - dt->getTexture()->getSize().x/2, y - dt->getTexture()->getSize().y * 3/4));
}

void CoucheDecor::addDecor(Decor *d)
{
    decors.insert(*d);
}


void CoucheDecor::removeDecor(int x, int y)
{
    const Decor *d = getDecor(x,y);
    if(d != nullptr)
      decors.erase(*d);
}

}
