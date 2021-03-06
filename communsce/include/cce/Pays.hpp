#ifndef CCE_PAYS_HPP
#define CCE_PAYS_HPP

#include <string>
#include <list>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp>
#include "cce/Region.hpp"
#include "cce/PointSpawn.hpp"

using std::string;
using std::list;
using boost::serialization::make_nvp;

namespace cce {

class Decor;

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


///\brief regions du pays
///\return Retourne les regions du pays
///
    map<string,Region>* getRegions();

    const map<string,Region>* getConstRegions() const;

///\brief obtenir une région
///\return Retourne une région associée à l'argument
///
    Region* getRegion(const string& nom);

///
///
///\brief point de spawn du pays
///\return Retourne le point de spawn du pays
///
    Decor* getPointSpawn();

///
///\brief point de spawn du pays
///\return Retourne le point de spawn du pays
///
    void setSpawn(Decor* d);

///
///\brief ajoute une région à la liste des régions
///\param r : regions a associer
///
    void addRegion(const string& name, const Region& r);

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
	(void) version;
        ar & make_nvp("income", income);
        ar & make_nvp("PointSpawn", spawn);
        ar & make_nvp("Regions", regions);
    }

protected :
    int income;
    map<string,Region> regions;
    Decor* spawn;
};
}
#endif // PAYS_HPP
