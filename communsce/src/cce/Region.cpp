#include "cce/Region.hpp"

namespace cce{

Region::Region(){
} 
Region::~Region()
{
}

int Region::getIncome(){
	return income;
}

string Region::getNom(){
	return nom;
}


polygon_concept Region::getZone(){
	return zone;
}

list<UpgradeTemplate> Region::getUpgrades(){
	return upgrades;
}

list<Tile> Region::getTiles(){
	return tiles;
}



Flag* Region::getFlag(){
	return flag;
}

}
