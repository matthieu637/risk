#ifndef CCE_REGION_HPP
#define CCE_REGION_HPP

#include <string>
#include <list>
#include "cce/Tile.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include "cce/UpgradeTemplate.hpp"
#include <boost/serialization/list.hpp>
#include "cce/Flag.hpp"
#include "cce/Polygon.hpp"

using std::string;
using std::list;

namespace cce {
  
class Region : public sf::Drawable
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
///\brief zone de la region
///\return Retourne la zone de la region
///
    Polygon* getZone();

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
    
    void setDraw(bool drawme);
    
    void resetPoly();

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      	
        (void)version;
        ar & make_nvp("income", income);
        ar & make_nvp("Flag", flag);
        ar & make_nvp("Polygon", zone);
        ar & make_nvp("Upgrades", upgrades);
        ar & make_nvp("Tiles",tiles);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    int income;
    Polygon zone;
    bool drawme;
    list<UpgradeTemplate> upgrades;
    list<Tile> tiles;
    Flag flag;
};
}
#endif
