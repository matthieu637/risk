#ifndef REGION_HPP
#define REGION_HPP

#include <list>
#include <string>
#include <cce/Region.hpp>

using std::string;
using std::list;


namespace cce{
class Tile;
class UpgradeTemplate;
class Flag;
class Polygon;
}

using cce::UpgradeTemplate;
using cce::Flag;
using cce::Tile;
using cce::Polygon;

namespace edt{
class Region : public cce::Region
{
public :
    Region(const Region& r);
    Region();
    virtual ~Region();
    
///
///\brief Reset le polygone (efface tous les points)
///\param x, y : les coordonnées
///
    void resetPolygon();
///
///\brief Ajoute un point de coordonnées x,y à la region
///\param x, y : les coordonnées
///
    void addPoint(int x, int y);
  
///
///\brief Definit l'income de la region
///\param incom : income à associer
///
    void setIncome(int income);
    
///
///\brief ajoute un upgrade dans la liste e des upgrades
///\param upgr : upgrades à associer
///
    void addUpgrade(const UpgradeTemplate& upgr);
    
///
///\brief ajoute une tile à la liste des tiles
///\param t : tiles à associer
///
    void setTiles(const Tile& t);
    
///
///\brief Definit le flag d'une region
///\param f : flag à associer
///
    void setFlag(cce::Decor* d);
    
    void setZone(const Polygon* p);
    
};
}
#endif // REGION_HPP
