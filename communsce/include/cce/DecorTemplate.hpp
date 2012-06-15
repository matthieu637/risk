#ifndef DECORTEMPLATE_HPP
#define DECORTEMPLATE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>

using sf::Texture;
using boost::serialization::make_nvp;
using std::string;

namespace cce{

class DecorTemplate
{

public:
    DecorTemplate();
    virtual ~DecorTemplate();
    
///
///\brief Texture du Decor
///\return Retourne la texture du Decor
///
    Texture* getTexture();
    
///
///\brief ID du decor
///\return Retourne l'id du DecorTemplate
///
    int getID();
    
///
///\brief Le Decor est-elle passable?
///\return Retourne true si le Decor bloque le pathing
///
    bool bloquant();
    
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      	ar & make_nvp("id", id);
	ar & make_nvp("path", path);
	ar & make_nvp("bloquante", bloquant_);
        boost::serialization::split_member(ar, *this, version);
    }
    
    template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
        (void) version;
	(void) ar;
    }
    
    template<class Archive>
    void load( Archive & ar, const unsigned int file_version ) {
	(void) file_version;
	(void) ar;
	loadTexture();
    }
    
private:
  void loadTexture();
    
private:
    int id;
    bool bloquant_;
    string path;
    Texture *texture;
};

}
#endif // DECORTEMPLATE_HPP
