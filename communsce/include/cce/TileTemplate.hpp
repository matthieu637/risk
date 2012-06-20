#ifndef TILETEMPLATE_HPP
#define TILETEMPLATE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <boost/serialization/nvp.hpp>
#include "bib/Logger.hpp"

using sf::Texture;
using boost::serialization::make_nvp;
using std::string;

namespace cce{

class TileTemplate
{

public:
    TileTemplate();
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
    int getID() const;
    
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
    
///
///\brief path du fichier image associé
///\return path de l'image sous forme de string
///
    string getPath(){return path;}
    
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
	(void) version;
	ar & make_nvp("path", path);
	ar & make_nvp("bloquante", bloquante_);
    }

  void loadAfterXML(int id);
    
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
