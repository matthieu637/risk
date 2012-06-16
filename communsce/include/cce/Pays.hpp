#ifndef CCE_PAYS_HPP
#define CCE_PAYS_HPP

#include <string>
#include <list>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp> 

using std::string;
using std::list;
using boost::serialization::make_nvp; 

namespace cce{
class Region; 
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
            list<Region> getRegions();
	    

///	    
///
///\brief point de spawn du pays
///\return Retourne le point de spawn du pays
///
            PointSpawn* getPointSpawn();
	    

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & make_nvp("nom", nom); 
	ar & make_nvp("income", income);
	ar & make_nvp("pointspawn", ps);
	ar & make_nvp("regions", regions);
    }
    
protected : 
	    int income;
	    string nom;
	    list<Region> regions;
	    PointSpawn* ps;	  

};
}
#endif // PAYS_HPP
