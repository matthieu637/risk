#ifndef TILE_HPP
#define TILE_HPP

#include <boost/serialization/nvp.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
///\param tt : Template utilisé pour le dessin
///	  x : ligne de la tile
///	  y : colonne de la tile
///
    void init(TileTemplate *tt, int x, int y);
    
///
///\brief Retourne le Template de la tile
///\return Retourne le Template de la tile
///
    TileTemplate* getTemplate() const;
    
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
        (void) version;
        ar & make_nvp("id", id);
    }

private:
    TileTemplate *tt;
    int id;
};

}
#endif // TILE_HPP
