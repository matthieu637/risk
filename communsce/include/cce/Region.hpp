#ifndef REGION_HPP
#define REGION_HPP

#include <string>
#include <boost/polygon/polygon.hpp>
#include <list>
#include "cce/Tile.hpp"
#include "cce/UpgradeTemplate.hpp"

using boost::polygon::polygon_concept;
using std::string;
using std::list;
	
namespace cce{

class Flag;	
class Region
{
	
public:
	    Region(int _income, string _nom, polygon_concept _zone, list<UpgradeTemplate> _upgrades, list<Tile> _tiles, Flag* _flag);
	    virtual ~Region();

///
///\brief income de la region
///\return Retourne l'income de la region
///
	    int getIncome();

///
///\brief Definit l'income de la region
///\param incom : income à associer
///
	    void setIncome(int incom);

///
///\brief nom de la region
///\return Retourne le nom de la region
///
	    string getNom();
///
///\brief Definit le nom de la region
///\param n : nom à associer
///
            void setNom(string n);
///
///\brief zone de la region
///\return Retourne la zone de la region
///
            polygon_concept getZone();
///
///\brief Definit la zone d'une region
///\param zon : zone à associer
///
            void setZone(polygon_concept zon);
///
///\brief upgrades de la region
///\return Retourne les upgrades de la region
///
            list<UpgradeTemplate> getUpgrades();
///
///\brief Definit les upgrades d'une region
///\param upgr : upgrades à associer
///
            void setUpgrades(list<UpgradeTemplate> upgr);	    
///
///\brief tiles de la region
///\return Retourne les tiles de la region
///
            list<Tile> getTiles();
///
///\brief Definit les tiles d'une region
///\param t : tiles à associer
///
            void setTiles(list<Tile> t);
///
///\brief flag de la region
///\return Retourne le flag de la region
///
            Flag* getFlag();
///
///\brief Definit le flag d'une region
///\param f : flag à associer
///
            void setFlag(Flag* f);



private:
	    int income;
	    string nom;
	    polygon_concept zone;
	    list<UpgradeTemplate> upgrades;
	    list<Tile> tiles;
	    Flag* flag;	    
};
}
#endif
