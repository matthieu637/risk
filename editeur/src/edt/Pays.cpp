#include "edt/Pays.hpp"
#include "edt/Region.hpp"

namespace edt {
  
Pays::Pays(int _income, PointSpawn* _ps)
{
    income = _income;
    ps = _ps;
}

Pays::Pays()
{

}

Pays::~Pays()
{

}

void Pays::setIncome(int income){
    this->income = income;
}

void Pays::setPointSpawn(PointSpawn* p){
    ps = p;
}
  
} 
