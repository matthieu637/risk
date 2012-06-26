#include "edt/Region.hpp"
#include "cce/Polygon.hpp"

using cce::Point;
using cce::Polygon;

namespace edt{

Region::Region(int _income, Polygon* _zone, list<UpgradeTemplate> _upgrades, list<Tile> _tiles, Flag* _flag)
{
    income = _income;
    zone = *_zone;
    upgrades = _upgrades;
    tiles = _tiles;
    flag = _flag;
}

Region::Region()
{
}

Region::~Region()
{
}

void Region::resetPolygon()
{
    zone.~Polygon();
    zone = Polygon();
}

void Region::addPoint(int x, int y)
{
    zone.addPoint(Point(x,y));
}

void Region::setIncome(int income){
    this->income = income;
}

void Region::addUpgrade(const UpgradeTemplate& upgr){
    upgrades.push_back(upgr);
}

void Region::setTiles(const Tile& t){
    tiles.push_back(t);
}

void Region::setFlag(Flag* f){
    flag = f;
}

}

