#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include <list>
#include "Vue.hpp"

namespace cce{
  class Pays;
  class Region;
}

namespace cli{
  
enum player_color {
  rouge, bleu, vert, violet, jaune, orange
};

class Joueur
{

public:
  Joueur(int num, player_color couleur);
  virtual ~Joueur();
  
  void addPays(cce::Pays* p);

  void addRegion(cce::Region* r);

  void removePays(cce::Pays* p);

  void removeRegion(cce::Region* r);
  
  list<cce::Region*> getRegions();
    
  list<cce::Pays*> getPays();
  
  int getIncome();
  
  int getGold();

private:
  int player_number, income, gold;
  player_color color;
  list<cce::Pays*> pays_controles;
  list<cce::Region*> regions_controles;
};

}

#endif // JOUEUR_HPP
