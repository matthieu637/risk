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

///
///\brief Pour ordonner l'unité de bouger quelque part, se met en mode "move"
///
      void orderMove(sf::Vector2i point);

///
///\brief Appliquer les ordres reçus
///
      void applyOrder();

///
///\brief Renvoie le vecteur entre position et socle
///
      sf::Vector2f getSocle();

///
///\brief Ordre courant
///\return order: l'ordre courant
///
      order getOrder();
      
  private:
      void deplacer();
    
    private :
	cce::UnitTemplate *unitTemplate;
	sf::Vector2f destination;
	sf::Vector2f socle;
	order current_order;
  };

}
#endif // UNIT_HPP