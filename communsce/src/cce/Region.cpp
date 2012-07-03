#include "cce/Region.hpp"
#include "cce/Polygon.hpp"
#include "cce/Flag.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace cce {

Region::Region() {
    drawme=false;
    flag=nullptr;
}

Region::~Region()
{
}

void Region::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(drawme)
        target.draw(zone, states);
}

void Region::setDraw(bool drawme)
{
    this->drawme=drawme;
}

int Region::getIncome() {
    return income;
}

Polygon* Region::getZone() {
    return &zone;
}

list<UpgradeTemplate> Region::getUpgrades() {
    return upgrades;
}

list<Tile> Region::getTiles() {
    return tiles;
}

Decor* Region::getFlag() {
    return flag;
}

void Region::resetPoly()
{
    zone.setPointCount(0);
}

}
