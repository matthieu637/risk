#ifndef CCE_UNIVERS_HPP
#define CCE_UNIVERS_HPP

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
    //obligatoire pour éviter des problèmes d'interdépance
    // et de singleton non initialisé
    void init();

    TileTemplate* getTileTemplate(int id);

    DecorTemplate* getDecorTemplate(int id);

    UnitTemplate* getUnitTemplate(int id);

    UpgradeTemplate* getUpgradeTemplate(int id);
    
    map<int, TileTemplate>* getMapTile();
    
    const map<int, DecorTemplate>* getMapDecor();
    
    const map<int, UnitTemplate>* getMapUnit();
    
    const map<int, UpgradeTemplate>* getMapUpgrade();

private:
    void chargerTileTemplates();
    void chargerDecorTemplates();
    void chargerUnitTemplates();

private:
    map<int, TileTemplate> *tileTemplate;
    map<int, DecorTemplate> *decorTemplate;
    map<int, UnitTemplate> *unitTemplate;
    map<int, UpgradeTemplate> *upgradeTemplate;
};

}

#endif // UNIVERS_HPP
