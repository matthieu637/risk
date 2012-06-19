#ifndef CCE_CARTE_HPP
#define CCE_CARTE_HPP


///
///\file Carte.hpp
///\brief Contient les informations necessaire pour une carte
///\author matthieu
///

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "Repere.hpp"
#include "CoucheDecor.hpp"
#include <list>
#include <string>
#include "Pays.hpp"

using boost::serialization::make_nvp;
using std::list;
using std::string;

namespace cce {
  
class Carte : public sf::Drawable
{

public:
///
///\brief Carte vide pour la créer via XML
///
  Carte();
///
///\brief Méthode de serialization pour l'écriture et la lecture en XML
///
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
	(void) version;
	ar & make_nvp("Repere", repere);
	ar & make_nvp("Pays", lp);
    }
    
    Repere* getRepere(){return &repere;}
    CoucheDecor* getCoucheDecor(){return &couche_decor;}
    list<Pays>* getListPays(){return &lp;}
    list<Region> getListRegions();
    
///
///\brief Ajouter une region a un pays par leurs noms.
///
    void addRegion(string nom_pays, string nom_region);
   
  
protected:
///
///\brief Méthode d'affichage SFML
///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
protected:
    Repere repere;
    CoucheDecor couche_decor;
    list<Pays> lp;
};

}

#endif // CCE_CARTE_HPP
