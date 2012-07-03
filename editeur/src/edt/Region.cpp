#include "edt/Region.hpp"
#include "cce/Polygon.hpp"

using cce::Point;
using cce::Polygon;

namespace edt{

Region::Region(const Region& r)
{
    income = r.income;
    zone = r.zone;
    upgrades = r.upgrades;
    tiles = r.tiles;
    flag = r.flag;
}

Region::Region()
{
}

Region::~Region()
{
}

void Region::setZone(const Polygon* p)
{
  zone = *p;
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

void Region::setFlag(cce::Decor* d){
    flag = d;
}

}

