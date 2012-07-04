#ifndef UNIT_HPP
#define UNIT_HPP

#include "cce/Decor.hpp"
#include "cce/Animation.hpp"
#include "cce/UnitTemplate.hpp"
#include <set>

using std::set;

namespace cli{
  
  enum order
  {
      stop, hold, move, follow, attack
  };
  
  class Joueur;
  class Modele;
  
  class Unit : public cce::Decor
  {
    public:
      Unit();
      ~Unit();
      Unit(Modele* ma, Joueur* joueur);
      void setUnitTemplate(cce::UnitTemplate *ut);
      void setId(int id);
///
///\brief Pour ordonner l'unité d'arreter son action, se met en mode "stop"
///
      void orderStop();
///
///\brief Pour ordonner l'unité de bouger quelque part, se met en mode "move"
///
      void orderMove(sf::Vector2i point);
      
      void animate();

///
///\brief Ordonner à l'unité d'en suivre une autre, se met en mode "follow"
///
      void orderFollow(Unit* to_follow);

///
///\brief Ordonne à l'unité d'en attaquer une autre, se met en mode "attack"
///      
      void orderAttack(Unit* to_attack);

///
///\brief Vérifie si des unités ennemies sont à portée d'aggro.
///
      void checkAggro();

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
///\brief Teste si l'unité est morte.
///
      bool isDead();
///
///\brief Ordre courant
///\return order: l'ordre courant
///
      order getOrder();

///
///\brief ajouter un traqueur à cette unité
///
      void addTraqueur(Unit* traqueur);

///
///\brief enlève un traqueur à cette unité
///
      void removeTraqueur(Unit* traqueur);

///
///\brief joueur propriétaire
///
      Joueur* getOwner();

      
    private:
	void deplacer();
    
    private :
	cce::UnitTemplate *unitTemplate;
	cce::Animation* anim;
	
	sf::Vector2f destination, deplacement;
	order current_order;
	Unit* target_unit;
	float distance_min_follow;
	bool attaque_prete;
	int current_hp, distance_aggro;
	Joueur* owner;
	Modele* m;
	set<Unit*> traqueurs;

  };

}
#endif // UNIT_HPP