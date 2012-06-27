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

map<string,Region>* Pays::getRegions() {
    return &regions;
}

const map<string,Region>* Pays::getConstRegions() const{
    return &regions;
}

Region* Pays::getRegion(const string& nom)
{
    return &regions[nom];
}

const PointSpawn* Pays::getPointSpawn(){
    return ps;
}

void Pays::addRegion(const string& name, const Region& r){
    regions[name] = r;
}

void Pays::setSpawn(const PointSpawn* d)
{
    ps = d;
}

}