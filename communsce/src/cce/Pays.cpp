#include "cce/Pays.hpp"
#include "cce/Region.hpp"


namespace cce{

Pays::Pays()
{
}

Pays::~Pays()
{

}

int Pays::getIncome(){
	return income;
}

string Pays::getNom(){
	return nom;
}

list<Region> Pays::getRegions(){
	return regions;
}

PointSpawn* Pays::getPointSpawn(){
	return ps;
}

}