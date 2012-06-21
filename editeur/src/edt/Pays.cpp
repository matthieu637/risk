#include "edt/Pays.hpp"
#include "edt/Region.hpp"

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

void Pays::setIncome(int income){
    this->income = income;
}

void Pays::setNom(string n){
    nom = n;
}

void Pays::setPointSpawn(PointSpawn* p){
    ps = *p;
}
  
} 
