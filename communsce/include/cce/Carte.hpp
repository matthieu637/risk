#ifndef CCE_CARTE_HPP
#define CCE_CARTE_HPP

#include <boost/serialization/nvp.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "Repere.hpp"

using boost::serialization::make_nvp;

namespace cce {

class Carte : public sf::Drawable
{

public:
  ///
///\brief Méthode à définir obligatoirement pour la serialization
///       BOOST_SERIALIZATION_NVP(id) <=> make_nvp("id", hot);
///
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void) version;
        ar & make_nvp("Repere", repere);
    }
  
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Carte();
private:
    Repere repere;
};

}

#endif // CCE_CARTE_HPP
