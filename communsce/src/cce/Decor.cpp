#include "cce/Decor.hpp"
#include "cce/DecorTemplate.hpp"
#include "bib/Logger.hpp"

using namespace std;

namespace cce {

Decor::Decor(DecorTemplate *_dt, int x, int y) : Sprite()
{
    dt = _dt;
    setTexture(dt->getTexture());
    dt->initAnimation(&animathor);
    
    animate();
    
    socle = sf::Vector2f(getLocalBounds().width/2, getLocalBounds().height - getLocalBounds().width/2 * (86.f/156.f));
    socleGlobal = getPosition() + getSocleCenter();
    
    selection_circle = new sf::CircleShape(); //avant setPosition qui le repositionne (sinon seg fault)
    selection_circle->setRadius(getSocleCenter().x);
    selection_circle->setOutlineThickness(3);
    selection_circle->setOutlineColor(sf::Color(0,150,0,255));
    selection_circle->setFillColor(sf::Color(0,0,0,0));
    selection_circle->setPosition(getPosition().x, getPosition().y + getSocleCenter().y - getSocleCenter().x);
    
    setPosition(x,y);
}

Decor::Decor()
{
    dt = nullptr;
    selection_circle = new sf::CircleShape();
}

Decor::~Decor()
{
    delete selection_circle;
}

void Decor::animate() {
    // Update animator and apply current animation state to the sprite
    animathor.update(frameClock.restart());
    animathor.animate(*this);
}

DecorTemplate* Decor::getTemplate() const
{
    return dt;
}


void Decor::setTexture(Texture* texture)
{
    Sprite::setTexture(*texture, true);

    yCompare = getPosition().y + getLocalBounds().height *3/4;
}

void Decor::move(float offsetX, float offsetY)
{
    Sprite::move(offsetX, offsetY);
    updatePosition();
}

void Decor::setPosition(float x, float y)
{
    Sprite::setPosition(x, y);
    updatePosition();
}

void Decor::setPosition(const sf::Vector2f& position)
{
    Sprite::setPosition(position);
    updatePosition();
}

void Decor::updatePosition()
{
    yCompare = getPosition().y + getLocalBounds().height *3/4;
    socleGlobal = getPosition() + getSocleCenter();
    selection_circle->setPosition(getPosition().x, getPosition().y + getSocleCenter().y);
}

sf::CircleShape* Decor::getSelectionCircle()
{
    return selection_circle;
}

sf::Vector2f Decor::getSocleCenter()
{
    return socle;
}

sf::Vector2f Decor::getSocleCenterGlobal()
{
    return socleGlobal;
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

void Decor::unpause() {
    frameClock.restart();
}


}
