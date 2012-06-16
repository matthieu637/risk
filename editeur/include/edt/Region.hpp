#ifndef REGION_HPP
#define REGION_HPP

#include <string>
#include <boost/polygon/polygon.hpp>
#include <list>

using boost::polygon::polygon_concept;
using std::string;
using std::list;


namespace cce{
using cce::UpgradeTemplate;
using cce::Tile;
class Tile;
class UpgradeTemplate;

}
namespace edt{
class Region
{
public :
   Region(int _income, string _nom, polygon_concept _zone, list<UpgradeTemplate> _upgrades, list<Tile> _tiles, Flag* _flag);
    virtual ~Region();
  
///
///\brief Definit l'income de la region
///\param incom : income à associer
///
	    void setIncome(int incom);
	    
///
///\brief Definit le nom de la region
///\param n : nom à associer
///
            void setNom(string n);
	    
///
///\brief Definit la zone d'une region
///\param zon : zone à associer
///
            void setZone(polygon_concept zon);
	    
///
///\brief Definit les upgrades d'une region
///\param upgr : upgrades à associer
///
            void setUpgrades(list<UpgradeTemplate> upgr);
	    
///
///\brief Definit les tiles d'une region
///\param t : tiles à associer
///
            void setTiles(list<Tile> t);
	    
///
///\brief Definit le flag d'une region
///\param f : flag à associer
///
            void setFlag(Flag* f);
	    
};
}
#endif // REGION_HPP
