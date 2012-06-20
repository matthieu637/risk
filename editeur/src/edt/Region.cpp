#include "edt/Region.hpp"

namespace edt{
  
Region::Region(int _income, polygon_concept _zone, list<UpgradeTemplate> _upgrades, list<Tile> _tiles, Flag* _flag){

	income = _income;
	zone = _zone;	
	upgrades = _upgrades;
	tiles = _tiles;
	flag = *_flag;
}

Region::~Region()
{
}

void Region::setIncome(int incom){
	income = incom;
}

void Region::setZone(polygon_concept zon){
	zone = zon;
}

void Region::setUpgrades(const UpgradeTemplate& upgr){
	upgrades.push_back(upgr);
}

void Region::setTiles(const Tile& t){
	tiles.push_back(t);
}

void Region::setFlag(Flag* f){
	flag = *f;
}
}

