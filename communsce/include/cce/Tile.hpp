#ifndef TILE_HPP
#define TILE_HPP

#include <boost/serialization/nvp.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "TileTemplate.hpp"
#include "Univers.hpp"

using sf::Texture;
using sf::Sprite;
using boost::serialization::make_nvp;

namespace cce{
  
class TileTemplate;
  
class Tile : public Sprite
{

public:
    Tile();
    virtual ~Tile();
///
///\brief initialise la tile et sa position sur la carte ( afin de la dessiner )
/// 	  
///\param x : ligne de la tile
///	  y : colonne de la tile
///
    void init(int x, int y);
    
///
///\brief Retourne le Template de la tile
///\return Retourne le Template de la tile
///
    TileTemplate* getTemplate() const;
    
    int getID() const;
    
///
///\brief Defini le TileTemplate associe
///\param _tt : TileTemplate
///
    void setTemplate(TileTemplate *_tt);

///
///\brief Supprime la texture de la tile
///
    void unsetTemplate();
    
///
///\brief redefinition de Sprite::setPosition
///
void setPosition(float x, float y);


    template<class Archive>
    void serialize(Archive& ar, const unsigned int version){
        boost::serialization::split_member(ar, *this, version);
    }
    
    template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
        (void) version;
	(void) ar;
	int id = tt->getID();
	ar << make_nvp("id", id);
    }
    
    template<class Archive>
    void load( Archive & ar, const unsigned int file_version ) {
	(void) file_version;
	(void) ar;
	int id;
	ar >> make_nvp("id", id);
	setTemplate(Univers::getInstance()->getTileTemplate(id));
    }

private:
    TileTemplate *tt;
};

}
#endif // TILE_HPP
