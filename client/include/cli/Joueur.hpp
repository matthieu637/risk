#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include <list>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Vue.hpp"

using std::vector;

namespace cce{
  class Pays;
  class Region;
}

namespace cli{
  
enum player_color {
  rouge, bleu, vert, violet, jaune, orange
};

class Unit;

class Joueur
{

public:
  Joueur();
  Joueur(int num, player_color couleur, int nbPlayers);
  virtual ~Joueur();
  
  ///
  ///\brief Ajoute un pays à ceux possédés, ajoute l'income du pays à l'income du joueur.
  ///
  void addPays(cce::Pays* p);
  
  ///
  ///\brief Ajoute une région à celles possédées, ajoute l'income de la région à l'income du joueur.
  ///
  void addRegion(cce::Region* r);
  
  ///
  ///\brief Enlève un pays à ceux possédés, soustrait l'income du pays à l'income du joueur.
  ///
  void removePays(cce::Pays* p);
  
  ///
  ///\brief Enlève une région à celles possédées, soustrait l'income de la région à l'income du joueur.
  ///
  void removeRegion(cce::Region* r);
  
  ///
  ///\brief Ajoute l'unité à ce joueur.
  ///
  void addUnit(Unit* u);
  
  ///
  ///\brief Enlève l'unité à ce joueur.
  ///
  void removeUnit(Unit* u);
  
  ///
  ///\brief Regions possédées par le joueur.
  ///
  list<cce::Region*> getRegions();
  
  ///
  ///\brief Pays possédées par le joueur.
  ///
  list<cce::Pays*> getPays();
  
  ///
  ///\brief Income total du joueur.
  ///
  int getIncome();
  
  ///
  ///\brief Gold disponible.
  ///
  int getGold();
  
  ///
  ///\brief Unités du joueur dans la région.
  ///
  list<Unit*> getUnitsInRect(sf::RectangleShape* rectangleSelection);
  
  ///
  ///\brief Changer le statut d'un joueur à son égard.
  ///\param num_joueur le numéro du joueur
  ///\param allied s'il devient allié ou ennemi
  ///
  void setAllied(int num_joueur, bool allied);
  
  ///
  ///\brief Tester si un joueur est allié ou ennemi selon son numéro
  ///
  bool isAllied(int num_joueur);

private:
  int player_number, income, gold;
  player_color color;
  list<cce::Pays*> pays_controles;
  list<cce::Region*> regions_controles;
  list<Unit*> units;
  vector<bool> allied_player;
};

}

#endif // JOUEUR_HPP
