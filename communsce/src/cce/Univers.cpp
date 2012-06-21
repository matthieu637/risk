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

    chargerTileTemplates();
    chargerDecorTemplates();
    chargerUnitTemplates();

    //std::map<int, UnitTemplate>::iterator it3(unitTemplate->begin()), it

    LOG_DEBUG("Univers sf chargé");
}

void Univers::chargerTileTemplates()
{
    tileTemplate = bib::XMLEngine::load< map<int, TileTemplate>>("TileTemplates", "data/univ/sf.tiletemplates");

    std::map<int,TileTemplate>::iterator it(tileTemplate->begin()), itEnd(tileTemplate->end());

    for(; it != itEnd; ++it)
        it->second.loadAfterXML(it->first);

    //bib::XMLEngine::save<map <int, TileTemplate>>(*tileTemplate, "TileTemplates", "tamere.xml");
}


void Univers::chargerDecorTemplates()
{
    decorTemplate = bib::XMLEngine::load< map<int, DecorTemplate>>("DecorTemplates", "data/univ/sf.decortemplates");
    std::map<int, DecorTemplate>::iterator it(decorTemplate->begin()), itEnd(decorTemplate->end());

    for(; it != itEnd; ++it)
        it->second.loadAfterXML(it->first);
}

void Univers::chargerUnitTemplates()
{
//     unitTemplate = new map<int, UnitTemplate>;
//     UnitTemplate ut;
//     unitTemplate->insert(std::pair<int, UnitTemplate>(20, ut));
//     bib::XMLEngine::save<map <int, UnitTemplate>>(*unitTempla*/te, "UnitTemplates", "tamere.xml");

    unitTemplate = bib::XMLEngine::load< map<int, UnitTemplate>>("UnitTemplates", "data/univ/sf.unittemplates");
    std::map<int, UnitTemplate>::iterator it(unitTemplate->begin()), itEnd(unitTemplate->end());

    for(; it != itEnd; ++it)
        it->second.loadAfterXML(it->first);
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

map<int, TileTemplate>* Univers::getMapTile(){return tileTemplate;}

map<int, DecorTemplate>* Univers::getMapDecor(){return decorTemplate;}

const map<int, UnitTemplate>* Univers::getMapUnit(){return unitTemplate;}

const map<int, UpgradeTemplate>* Univers::getMapUpgrade(){return upgradeTemplate;}

}

