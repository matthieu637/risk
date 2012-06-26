#include "cce/Region.hpp"
#include "cce/Polygon.hpp"
#include "cce/Flag.hpp"

namespace cce{

Region::Region(){
} 

Region::~Region()
{
}

int Region::getIncome(){
	return income;
}

Polygon* Region::getZone(){
	return &zone;
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
