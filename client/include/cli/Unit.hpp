#ifndef UNIT_HPP
#define UNIT_HPP
#include <cce/Decor.hpp>
#include <cce/UnitTemplate.hpp>

namespace cli{
  
  enum order
  {
      move, attack, hold, stop
  };
  
  class Unit : public cce::Decor
  {
    public:
      Unit();
      void setUnitTemplate(cce::UnitTemplate *ut);
      void setId(int id);
      void orderMove(sf::Vector2i point);
      void applyOrder();
      void deplacer();
    
    private :
	cce::UnitTemplate *unitTemplate;
	sf::Vector2i destination;
	order current_order;
  };

}
#endif // UNIT_HPP