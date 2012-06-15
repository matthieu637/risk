#include "edt/Region.hpp"

namespace edt{
  
Region::Region(int _income, string _nom, polygon_concept _zone, list<UpgradeTemplate> _upgrades, list<Tile> _tiles, Flag* _flag){

	income = _income;
	nom = _nom;
	zone = _zone;	
	upgrades = _upgrades;
	tiles = _tiles;
	flag = _flag;
}

void Region::setIncome(int incom){
	income = incom;
}

void Region::setNom(string n){
	nom = n;
}

void Region::setZone(polygon_concept zon){
	zone = zon;
}

void Region::setUpgrades(list<UpgradeTemplate> upgr){
	upgrades = upgr;
}

void Region::setTiles(list<Tile> t){
	tiles  = t;
}

void Region::setFlag(Flag* f){
	flag = f;
}
}

