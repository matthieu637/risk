#ifndef COUCHEDECORCLIENT_HPP
#define COUCHEDECORCLIENT_HPP
#include <cce/CoucheDecor.hpp>

#include <set>
#include <list>

using std::list;
using std::set;

namespace cli
{

class Unit;
  
class CoucheDecor: public cce::CoucheDecor{

public:
  
    CoucheDecor();

    ~CoucheDecor();
    
    void init();
    
    void addUnit(Unit* u);
    
    void removeUnit(Unit* u);

///
///\brief liste des unités dont le socle est dans le rectangle
///
    list<Unit*> getUnitsInRect(sf::RectangleShape* rectangleSelection);

///
///\brief unité visible au point cliqué
///
    Unit* getUnit(sf::Vector2f position);

///
///\brief liste exhaustive des unités
///
    list<Unit*>* getAllUnits();

private:
    list<Unit*>* allUnits;
};

}

#endif // COUCHEDECOR_HPP
