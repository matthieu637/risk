#ifndef UNIVERS_HPP
#define UNIVERS_HPP

#include <map>
#include "bib/Singleton.hpp"

using std::map;

namespace cce {

class TileTemplate;
class DecorTemplate;
class UnitTemplate;
class UpgradeTemplate;

class Univers : public bib::Singleton<Univers>
{
    friend class bib::Singleton<Univers>;

protected:
    Univers();
    virtual ~Univers();
    
public:
    TileTemplate* getTileTemplate(int id);

    DecorTemplate* getDecorTemplate(int id);

    UnitTemplate* getUnitTemplate(int id);

    UpgradeTemplate* getUpgradeTemplate(int id);
    
private:
    map<int, TileTemplate> *tileTemplate;
    map<int, DecorTemplate> *decorTemplate;
    map<int, UnitTemplate> *unitTemplate;
    map<int, UpgradeTemplate> *upgradeTemplate;
};

}

#endif // UNIVERS_HPP
