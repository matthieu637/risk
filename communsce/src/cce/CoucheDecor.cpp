#include "cce/CoucheDecor.hpp"
#include "cce/Decor.hpp"
#include "cce/DecorTemplate.hpp"
#include "cce/UnitTemplate.hpp"
#include "bib/Logger.hpp"

namespace cce {

CoucheDecor::CoucheDecor()
{
}

CoucheDecor::~CoucheDecor()
{

}

Decor* CoucheDecor::getDecor(int x, int y)
{
    int a;
    set<Decor*>::reverse_iterator rit;
    for(rit = decors.rbegin(); rit != decors.rend(); rit++) {
        if((*rit)->getGlobalBounds().contains(x, y)) {
            a = (*rit)->getTexture()->copyToImage().getPixel(x - (*rit)->getPosition().x, y - (*rit)->getPosition().y).a;
            if(a > 122) //pixel transparent? Permet de détecter véritablement le decor cliqué lorsqu'ils sont superposés
                return *rit;
        }
    }
    return nullptr;
}

void CoucheDecor::setDecorMove(int x, int y) {
    d_move = getDecor(x, y);
}

void CoucheDecor::moveDecor(int dx, int dy)
{
    if(d_move == nullptr)
        return;
    decors.erase(d_move);
    d_move->move(dx, dy);
    if(decors.count(d_move) > 0)
        d_move->move(-dx, -dy);
    decors.insert(d_move);
}

void CoucheDecor::update()
{
    set<Decor*>::iterator it = decors.begin();
    for(; it != decors.end(); ++it) {
        cce::Decor* dd = *it;
        dd->animate();
    }
}

void CoucheDecor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    set<Decor*>::iterator it = decors.begin();
    for(; it != decors.end(); it++)
	target.draw(**it, states);
}

void CoucheDecor::addDecor(DecorTemplate *dt, int x, int y)
{
    Decor* d = new Decor(dt, x - dt->getTexture()->getSize().x/2, y - dt->getTexture()->getSize().y * 3/4);
    decors.insert(d);
    undoDecors.push(d);
    this->clearRedoDecors();
  
}

void CoucheDecor::addDecor(Decor *d)
{
    decors.insert(d);
    undoDecors.push(d);
    this->clearRedoDecors();
}


void CoucheDecor::removeDecor(int x, int y)
{
    Decor *d = getDecor(x,y);
    if(d != nullptr) {
        decors.erase(d);
    }
}

void CoucheDecor::undoDecor(){
  if(!undoDecors.empty()){
    while(undoDecors.top() == nullptr){
      redoDecors.pop();  
    }
    redoDecors.push(undoDecors.top());
    decors.erase(undoDecors.top());
    undoDecors.pop();
  }

}
    
void CoucheDecor::redoDecor(){
  if(!redoDecors.empty()){
    while(redoDecors.top() == nullptr){
      redoDecors.pop();
      return ;	  
    }
    undoDecors.push(redoDecors.top());
    redoDecors.top()->unpause();
    decors.insert(redoDecors.top());
    redoDecors.pop();
  }
}

void CoucheDecor::clearRedoDecors(){
  redoDecors = stack<Decor*>();
}

void CoucheDecor::removeDecor(Decor* d)
{
    if(d != nullptr)
        decors.erase(d);
}

}