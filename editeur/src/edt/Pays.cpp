#include "edt/Pays.hpp"
#include "edt/Region.hpp"
#include "cce/Region.hpp"


namespace edt {
  
Pays::Pays(int _income, string _nom, PointSpawn* _ps)
{
  income = _income;
  nom = _nom;
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

void Pays::addRegion(const Region& r){
	regions.push_back(r);
}

void Pays::setPointSpawn(PointSpawn* p){
	ps = p;
}
  
} 
