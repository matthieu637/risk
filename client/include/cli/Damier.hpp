#ifndef DAMIER_HPP
#define DAMIER_HPP

///
///\file Damier.hpp
///\brief Decoupage de la carte en vecteur 2 dimensions de sets contenant les unités,
///\brief pour un accès plus effcace aux unités selon leurs coordonnées.
///\author aymeric
///

#include <set>
#include <vector>
#include <list>
#include <SFML/Graphics/Rect.hpp>

using std::list;
using std::set;
using std::vector;

namespace cli{
  
class Unit;
class Joueur;

class Damier
{

public:
  Damier(int largeurRepere, int hauteurRepere);
  virtual ~Damier();
  
  void addUnit(Unit* u);
  
  void removeUnit(Unit* u);

///
///\brief unité visible au point cliqué
///
    Unit* getUnit(sf::Vector2f position);

///
///\brief liste des unités dont le socle est dans le rectangle
///
    list<Unit*> getUnitsInRect(sf::FloatRect* rectangleSelection);

///
///\brief unité ennemie la plus proche de position dans le cercle de rayon range.
///
    Unit* closestEnemyInRange(int range, sf::Vector2f position, Joueur* j);

///
///\brief savoir si un décor entre en collision avec un autre
///\param u: unit à tester
///\param position: la position où le tester
///\return true si ce décor entre en collision avec un autre à l'endroit indiqué
///
    bool collision(Unit* u, sf::Vector2f position);
    
private:
  
  set<Unit*>* getSquare(int ligne, int colonne);
  
  vector<vector<set<Unit*>*>*>* damier;
  
  static const int size_square_damier = 200;
  int nb_lignes, nb_colonnes;
};

}

#endif // DAMIER_HPP
