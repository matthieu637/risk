#ifndef UNIT_HPP
#define UNIT_HPP
#include <SFML/Graphics/CircleShape.hpp>
#include <cce/Decor.hpp>
#include <cce/UnitTemplate.hpp>

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

///
///\brief Ordonner à l'unité d'en suivre une autre
///
      void orderFollow(Unit* to_follow);

///
///\brief Appliquer les ordres reçus
///
      void applyOrder();

///
///\brief Renvoie le vecteur entre position et socle
///
      sf::Vector2f getSocleCenter();

///
///\brief Ordre courant
///\return order: l'ordre courant
///
      order getOrder();

///
///\brief le cercle apparaissant sous l'unité lorsqu'elle fait partie de la sélection courante
///\return le cercle CircleShape.
///
      sf::CircleShape* getSelectionCircle();
      
  private:
      void deplacer(sf::Vector2f destination);
    
    private :
	cce::UnitTemplate *unitTemplate;
	sf::Vector2f destination;
	order current_order;
	Unit* followed_unit;
	float distance_min_follow;
	sf::CircleShape* selection_circle;
	sf::Vector2f socle;
  };

}
#endif // UNIT_HPP