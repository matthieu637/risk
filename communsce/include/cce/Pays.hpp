#ifndef CCE_PAYS_HPP
#define CCE_PAYS_HPP

#include <string>
#include <list>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp> 
#include "Region.hpp"
#include "cce/PointSpawn.hpp"

using std::string;
using std::list;
using boost::serialization::make_nvp; 

namespace cce{
class PointSpawn;
class Pays
{

public:
Pays();
virtual ~Pays();

///
///\brief income du pays
///\return Retourne l'income du pays
///
	    int getIncome();

///
///\brief nom du pays
///\return Retourne le nom du pays
///
	    string getNom();

	    
///\brief regions du pays
///\return Retourne les regions du pays
///
            map<string,Region>* getRegions();
	    
///\brief obtenir une région
///\return Retourne une région associée à l'argument 
///
            Region getRegion(string nom);
	    
///	    
///
///\brief point de spawn du pays
///\return Retourne le point de spawn du pays
///
            PointSpawn* getPointSpawn();
	    
///
///\brief ajoute une région à la liste des régions
///\param r : regions a associer
///
            void addRegion(const string& name, const Region& r);  
	    

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
	(void) version;
        ar & make_nvp("nom", nom); 
	ar & make_nvp("income", income);
	ar & make_nvp("PointSpawn", ps);
	ar & make_nvp("Regions", regions);
    }
    
protected : 
	    int income;
	    string nom;
	    map<string,Region> regions;
	    PointSpawn ps;	  

};
}
#endif // PAYS_HPP
