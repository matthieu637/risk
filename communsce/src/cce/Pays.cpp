#include "cce/Pays.hpp"

namespace cce{

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

int Pays::getIncome(){
	return income;
}

void Pays::setIncome(int incom){
	income = incom;
}

string Pays::getNom(){
	return nom;
}

void Pays::setNom(string n){
	nom = n;
}


list<Region> Pays::getRegions(){
	return regions;
}

void Pays::setRegions(list<Region> r){
	regions  = r;
}

PointSpawn* Pays::getPointSpawn(){
	return ps;
}

void Pays::setPointSpawn(PointSpawn* p){
	ps = p;
}
}