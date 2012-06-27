#ifndef PAYS_HPP
#define PAYS_HPP

#include <string>
#include <list>
#include <cce/Pays.hpp>


using std::string;
using std::list;

namespace cce{
  class Decor;
}

using cce::Decor;

namespace edt{
class Region;
  
class Pays : public cce::Pays
{
public:
    Pays(int _income, Decor* _ps);
    Pays();
    virtual ~Pays();

///
///\brief definit l'income du pays
///\param incom : income à associer
///
    void setIncome(int income);
};
}
#endif // PAYS_HPP
