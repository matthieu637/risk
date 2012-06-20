#ifndef REGION_HPP
#define REGION_HPP

#include <string>
#include <boost/polygon/polygon.hpp>
#include <list>
#include <cce/Region.hpp>

using boost::polygon::polygon_concept;
using std::string;
using std::list;


namespace cce{
class Tile;
class UpgradeTemplate;
class Flag;
}
using cce::UpgradeTemplate;
using cce::Flag;
using cce::Tile;

namespace edt{
class Region : public cce::Region
{
public :
   Region(int _income, polygon_concept _zone, list<UpgradeTemplate> _upgrades, list<Tile> _tiles, Flag* _flag);
    virtual ~Region();
  
///
///\brief Definit l'income de la region
///\param incom : income à associer
///
	    void setIncome(int incom);
	    
///
///\brief Definit la zone d'une region
///\param zon : zone à associer
///
            void setZone(polygon_concept zon);
	    
///
///\brief ajoute un upgrade dans la liste e des upgrades
///\param upgr : upgrades à associer
///
            void setUpgrades(const UpgradeTemplate& upgr);
	    
///
///\brief ajoute une tile à la liste des tiles
///\param t : tiles à associer
///
            void setTiles(const Tile& t);
	    
///
///\brief Definit le flag d'une region
///\param f : flag à associer
///
            void setFlag(Flag* f);
	    
	    
};
}
#endif // REGION_HPP
