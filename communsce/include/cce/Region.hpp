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
	    Region();
	    virtual ~Region();

///
///\brief income de la region
///\return Retourne l'income de la region
///
	    int getIncome();

///
///\brief nom de la region
///\return Retourne le nom de la region
///
	    string getNom();

///
///\brief zone de la region
///\return Retourne la zone de la region
///
            polygon_concept getZone();

///
///\brief upgrades de la region
///\return Retourne les upgrades de la region
///
            list<UpgradeTemplate> getUpgrades();
	    
///
///\brief tiles de la region
///\return Retourne les tiles de la region
///
            list<Tile> getTiles();

///
///\brief flag de la region
///\return Retourne le flag de la region
///
            Flag* getFlag();
	    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & make_nvp("nom", nom); 
	ar & make_nvp("income", income);
	ar & make_nvp("flag", flag);
	ar & make_nvp("zone", zone);
    }


protected:
	    int income;
	    string nom;
	    polygon_concept zone;
	    list<UpgradeTemplate> upgrades;
	    list<Tile> tiles;
	    Flag* flag;	    
};
}
#endif
