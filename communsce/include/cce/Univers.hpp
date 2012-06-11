#ifndef UNIVERS_HPP
#define UNIVERS_HPP

#include <map>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp>
#include "cce/TileTemplate.hpp"
#include "cce/DecorTemplate.hpp"
#include "cce/UnitTemplate.hpp"
#include "cce/UpgradeTemplate.hpp"


using std::map;
using boost::serialization::make_nvp;

namespace cce {

class TileTemplate;
class DecorTemplate;
class UnitTemplate;
class UpgradeTemplate;

class Univers
{

public:
    Univers();
    virtual ~Univers();

    TileTemplate* getTileTemplate(int id);

    DecorTemplate* getDecorTemplate(int id);

    UnitTemplate* getUnitTemplate(int id);

    UpgradeTemplate* getUpgradeTemplate(int id);

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        (void) version;
	ar & make_nvp("tileTemplate", tileTemplate);
    }

private:
    map<int, TileTemplate> tileTemplate;
    map<int, DecorTemplate> decorTemplate;
    map<int, UnitTemplate> unitTemplate;
    map<int, UpgradeTemplate> upgradeTemplate;
};

}

#endif // UNIVERS_HPP
