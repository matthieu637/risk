#include "cce/Univers.hpp"

#include <boost/serialization/map.hpp>
#include "cce/TileTemplate.hpp"
#include "cce/DecorTemplate.hpp"
#include "cce/UnitTemplate.hpp"
#include "cce/UpgradeTemplate.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/ImageManager.hpp"

namespace cce {

Univers::Univers()
{

}

void Univers::init()
{
    LOG_DEBUG("Début chargement univers sf");
    ImageManager::getInstance()->add_resource_directory("data/texture/");
    tileTemplate = bib::XMLEngine::load< map<int, TileTemplate>>("TileTemplates", "data/univ/sf.tiletemplates");
    decorTemplate = bib::XMLEngine::load< map<int, DecorTemplate>>("DecorTemplates", "data/univ/sf.decortemplates");
    
    //initilise tile
    std::map<int,TileTemplate>::iterator it(tileTemplate->begin()), itEnd(tileTemplate->end());
    std::map<int, DecorTemplate>::iterator it2(decorTemplate->begin()), it2End(decorTemplate->end());
    
    for(;it != itEnd; ++it)
      it->second.loadAfterXML(it->first);
    for(; it2 != it2End; ++it2End)
      it2->second.loadAfterXML(it2->first);
    
    
    //bib::XMLEngine::save<map <int, TileTemplate>>(*tileTemplate, "TileTemplates", "tamere.xml");
    LOG_DEBUG("Univers sf chargé");
}

Univers::~Univers()
{

}

TileTemplate* Univers::getTileTemplate(int id)
{
    return &tileTemplate->at(id);
}

DecorTemplate* Univers::getDecorTemplate(int id)
{
    return &decorTemplate->at(id);
}

UnitTemplate* Univers::getUnitTemplate(int id)
{
    return &unitTemplate->at(id);
}

UpgradeTemplate* Univers::getUpgradeTemplate(int id)
{
    return &upgradeTemplate->at(id);
}

}

