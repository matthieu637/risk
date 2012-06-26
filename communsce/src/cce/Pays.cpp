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

map<string,Region>* Pays::getRegions(){
    return &regions;
}

Region Pays::getRegion(string nom)
{
    return regions[nom];
}

PointSpawn* Pays::getPointSpawn(){
    return ps;
}

void Pays::addRegion(const string& name, const Region& r){
    regions[name] = r;
}

void Pays::setSpawn(PointSpawn* d)
{
    ps = d;
}

}