#ifndef UNIT_HPP
#define UNIT_HPP
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
///\brief Attaque si à portée, sinon déplacement.
///
      void attaquer();

///
///\brief Renvoie une quantité de degats aléatoire de l'intervalle [min,max]
///
      int rollDamage();

///
///\brief Appliquer les ordres reçus
///
      void applyOrder();

///
///\brief se fait attaquer
///\param type: le type de degats
///\param degats: les degats
///
      void takeDamages(cce::damage_type machin,int degats);

///
///\brief Ordre courant
///\return order: l'ordre courant
///
      order getOrder();
      
    private:
	void deplacer();
    
    private :
	cce::UnitTemplate *unitTemplate;
	sf::Vector2f destination, deplacement;
	order current_order;
	Unit* target_unit;
	float distance_min_follow;
	bool attaque_prete;
	int current_hp;
  };

}
#endif // UNIT_HPP