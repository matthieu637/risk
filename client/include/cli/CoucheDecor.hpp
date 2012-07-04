#ifndef COUCHEDECORCLIENT_HPP
#define COUCHEDECORCLIENT_HPP
#include <cce/CoucheDecor.hpp>

#include <set>
#include <list>

using std::list;
using std::set;

namespace cli
{

class Joueur;

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
    list<Unit*> getUnitsInRect(sf::FloatRect* rectangleSelection);

///
///\brief unité visible au point cliqué
///
    Unit* getUnit(sf::Vector2f position);

///
///\brief unité ennemie la plus proche de position dans le cercle de rayon range.
///
    Unit* closestEnemyInRange(int range, sf::Vector2f position, Joueur* j);

///
///\brief savoir si un décor entre en collision avec un autre
///\param d: le décor à tester
///\param position: la position où le tester
///\return true si ce décor entre en collision avec un autre à l'endroit indiqué
///
    bool collision(cce::Decor* d, sf::Vector2f position);

///
///\brief liste exhaustive des unités
///
    set<Unit*>* getAllUnits();

private:
    set<Unit*>* allUnits;
};

}

#endif // COUCHEDECOR_HPP
