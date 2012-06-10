#ifndef UNIVERS_HPP
#define UNIVERS_HPP

#include <map>
using std::map;

namespace cce{

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
    
private:
    map<int, TileTemplate*> tileTemplate;
    map<int, DecorTemplate*> decorTemplate;
    map<int, UnitTemplate*> unitTemplate;
    map<int, UpgradeTemplate*> upgradeTemplate;
};

}

#endif // UNIVERS_HPP
