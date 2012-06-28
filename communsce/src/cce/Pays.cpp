#include "cce/Pays.hpp"

namespace cce{

Pays::Pays()
{
  spawn = nullptr;
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

Decor* Pays::getPointSpawn(){
    return spawn;
}

void Pays::addRegion(const string& name, const Region& r){
    regions[name] = r;
}

void Pays::setSpawn(Decor* d)
{
    spawn = d;
}

}