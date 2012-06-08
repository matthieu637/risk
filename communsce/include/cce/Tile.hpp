#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "TileTemplate.hpp"

using sf::Texture;
using sf::Sprite;

namespace cce{
  
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
    void init(const TileTemplate *tt, int x, int y);
    

public:
///
///\brief Retourne le Template de la tile
///\return Retourne le Template de la tile
///
    TileTemplate* getTemplate() const;
    
///
///\brief Defini la texture de la tile
///\param id : id de la texture 
///
    void setTemplate(const TileTemplate *_tt);

///
///\brief Supprime la texture de la tile
///
    void unsetTemplate();
    
///
///\brief Definir les coordonnees de la tile en pixels
///
    void setCoordonnes(const int x, const int y);

private:
    TileTemplate *tt;

public:
private:
  int x, y;
};

}
#endif // TILE_HPP
