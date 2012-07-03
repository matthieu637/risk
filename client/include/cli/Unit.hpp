#ifndef UNIT_HPP
#define UNIT_HPP
#include "cce/Decor.hpp"
#include "cce/UnitTemplate.hpp"
#include "cce/Animation.hpp"

namespace cli{
  
  enum order
  {
      stop, hold, move, follow, attack
  };
  
  class Unit : public cce::Decor
  {
    public:
      Unit();
      void setUnitTemplate(cce::UnitTemplate *ut);
      void setId(int id);

///
///\brief Pour ordonner l'unité de bouger quelque part, se met en mode "move"
///
      void orderMove(sf::Vector2i point);
      
      void animate();

///
///\brief Ordonner à l'unité d'en suivre une autre
///
      void orderFollow(Unit* to_follow);

///
///\brief Appliquer les ordres reçus
///
      void applyOrder();

///
///\brief Ordre courant
///\return order: l'ordre courant
///
      order getOrder();
      
    private:
	void deplacer();
    
    private :
	cce::UnitTemplate *unitTemplate;
	cce::Animation* anim;
	
	sf::Vector2f destination, deplacement;
	order current_order;
	Unit* followed_unit;
	float distance_min_follow;

  };

}
#endif // UNIT_HPP