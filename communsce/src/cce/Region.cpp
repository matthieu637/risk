#include "cce/Region.hpp"
#include "cce/Flag.hpp"

namespace cce{

Region::Region(int _income, string _nom, polygon_concept _zone, list<UpgradeTemplate> _upgrades, list<Tile> _tiles, Flag* _flag){

	income = _income;
	nom = _nom;
	zone = zone;	
	upgrades = _upgrades;
	tiles = _tiles;
	flag = _flag;
}

Region::~Region()
{
}

int Region::getIncome(){
	return income;
}

void Region::setIncome(int incom){
	income = incom;
}

string Region::getNom(){
	return nom;
}

void Region::setNom(string n){
	nom = n;
}

polygon_concept Region::getZone(){
	return zone;
}

void Region::setZone(polygon_concept zon){
	zone = zon;
}

list<UpgradeTemplate> Region::getUpgrades(){
	return upgrades;
}

void Region::setUpgrades(list<UpgradeTemplate> upgr){
	upgrades = upgr;
}

list<Tile> Region::getTiles(){
	return tiles;
}

void Region::setTiles(list<Tile> t){
	tiles  = t;
}

Flag* Region::getFlag(){
	return flag;
}

void Region::setFlag(Flag* f){
	flag = f;
}
}
