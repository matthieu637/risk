#include "edt/Pays.hpp"
#include "edt/Region.hpp"
#include "cce/Region.hpp"


namespace edt {
  
Pays::Pays(int _income, string _nom, list<Region> _regions, PointSpawn* _ps)
{
  income = _income;
  nom = _nom;
  regions = _regions;
  ps = _ps;
}

Pays::~Pays()
{

}

void Pays::setIncome(int incom){
	income = incom;
}

void Pays::setNom(string n){
	nom = n;
}

void Pays::addRegions(list<Region> r){
	regions  = r;
}

void Pays::setPointSpawn(PointSpawn* p){
	ps = p;
}
  
} 
