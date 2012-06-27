#include "edt/Pays.hpp"
#include "edt/Region.hpp"

namespace edt {
  
Pays::Pays(int _income, Decor* _ps)
{
    income = _income;
    spawn = _ps;
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
  
} 
