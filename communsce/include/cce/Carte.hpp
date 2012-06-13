#ifndef CCE_CARTE_HPP
#define CCE_CARTE_HPP


///
///\file Carte.hpp
///\brief Contient les informations necessaire pour une carte
///\author matthieu
///

#include <boost/serialization/nvp.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "Repere.hpp"

using boost::serialization::make_nvp;

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
    }
    
    Repere* getRepere(){return &repere;}
  
protected:
///
///\brief Méthode d'affichage SFML
///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
protected:
    Repere repere;
};

}

#endif // CCE_CARTE_HPP
