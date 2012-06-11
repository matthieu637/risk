#ifndef TILETEMPLATE_HPP
#define TILETEMPLATE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>
#include "bib/Logger.hpp"

using sf::Texture;
using boost::serialization::make_nvp;
using std::string;

namespace cce{

class TileTemplate
{

public:
    TileTemplate();
    void init(int _id, bool _bloquante, string path);
    virtual ~TileTemplate();
    
///
///\brief Texture de la tile
///\return Retourne la texture de la tile
///
    Texture* getTexture();
    
///
///\brief ID de la tile
///\return Retourne l'id de la TileTemplate
///
    int getID();
    
///
///\brief Decalage en hauteur pour les tiles qui dépasse la hauteur conforme (brins d'herbe , ...)
///\return Retourne le decalage en pixels
///
    int getDecalageHauteur();
    
///
///\brief La tile est-elle passable?
///\return Retourne true si la Tile bloque le pathing
///
    bool bloquante();
    
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      	ar & make_nvp("id", id);
	ar & make_nvp("path", path);
	ar & make_nvp("bloquante", bloquante_);
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
	LOG_DEBUG("fucking here");
	std::cout << std::flush;
    }

    
private:
    int id, decalage_hauteur_image;
    string path;
    bool bloquante_;
    Texture *texture;
    
public:
    static const int hauteurTile = 88;
};

}

#endif // TILETEMPLATE_HPP
