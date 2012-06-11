#include "cce/Univers.hpp"
#include "cce/TileTemplate.hpp"
#include "cce/DecorTemplate.hpp"
#include "cce/UnitTemplate.hpp"
#include "cce/UpgradeTemplate.hpp"


namespace cce{

Univers::Univers()
{

}

Univers::~Univers()
{

}
    
TileTemplate* Univers::getTileTemplate(int id)
{
  return &(tileTemplate[id]);
}
    
DecorTemplate* Univers::getDecorTemplate(int id)
{
  return &(decorTemplate[id]);
}
    
UnitTemplate* Univers::getUnitTemplate(int id)
{
  return &(unitTemplate[id]);
}
    
UpgradeTemplate* Univers::getUpgradeTemplate(int id)
{
  return &(upgradeTemplate[id]);
}

}