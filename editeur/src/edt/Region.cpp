#include "edt/Region.hpp"

namespace edt{
  
cce::Region::Region(int _income, string _nom, polygon_concept _zone, list<UpgradeTemplate> _upgrades, list<Tile> _tiles, Flag* _flag){

	income = _income;
	nom = _nom;
	zone = _zone;	
	upgrades = _upgrades;
	tiles = _tiles;
	flag = _flag;
}

void cce::Region::setIncome(int incom){
	income = incom;
}

void cce::Region::setNom(string n){
	nom = n;
}

void cce::Region::setZone(polygon_concept zon){
	zone = zon;
}

void cce::Region::setUpgrades(list<UpgradeTemplate> upgr){
	upgrades = upgr;
}

void cce::Region::setTiles(list<Tile> t){
	tiles  = t;
}

void cce::Region::setFlag(Flag* f){
	flag = f;
}
}

