#ifndef TILETEMPLATE_HPP
#define TILETEMPLATE_HPP

#include <SFML/Graphics/Texture.hpp>

using sf::Texture;

namespace cce{

class TileTemplate
{

public:
    TileTemplate(int _id, bool _bloquante, Texture *_texture);
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
///\brief La tile est-elle passable?
///\return Retourne true si la Tile bloque le pathing
///
    bool bloquante();
    
private:
    int id;
    bool bloquante;
    Texture *texture;
};

}

#endif // TILETEMPLATE_HPP
