#include "cce/Carte.hpp"
#include "cce/Pays.hpp"
#include "cce/Region.hpp"

namespace cce {

Carte::Carte()
{

}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(repere, states);
    target.draw(couche_decor, states);

    map <string,Pays>::const_iterator it;
    map<string,Region>::const_iterator ir;
    for (it = mp.begin(); it != mp.end(); it++)
        for(ir=it->second.getConstRegions()->begin(); ir!=it->second.getConstRegions()->end(); ir++){
            target.draw(ir->second, states);
	}
}

map<string, Region* >* Carte::getAllRegions()
{
    map<string, Region* > *result= new map<string, Region* >;

    map <string,Pays>::iterator it;
    map<string,Region>::iterator ir;
    for (it = mp.begin(); it != mp.end(); it++)
        for(ir=it->second.getRegions()->begin(); ir!=it->second.getRegions()->end(); ir++)
            (*result)[ir->first] = &ir->second;
    return result;
}

void Carte::addRegion(const string& nom_pays, const string& nom_region, const Region& r)
{
    mp[nom_pays].addRegion(nom_region, r);
}

void Carte::addPays(const string& nom_pays, const Pays& p)
{
    mp[nom_pays] = p;
}

map<string, Pays>* Carte::getAllPays()
{
    return &mp;
}

Region* Carte::getRegion(const string& nom_region)
{
    map <string,Pays>::iterator it;
    for (it = mp.begin(); it != mp.end(); it++)
        if(it->second.getRegion(nom_region) != nullptr)
            return it->second.getRegion(nom_region);
    return nullptr;
}

Pays* Carte::getPays(const string& nom_pays)
{
    return &mp[nom_pays];
}


}
