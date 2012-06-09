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
///\brief Decalage en hauteur pour les tiles qui dépasse la hauteur conforme (brins d'herbe , ...)
///\return Retourne le decalage en pixels
///
    int getDecalageHauteur();
    
///
///\brief La tile est-elle passable?
///\return Retourne true si la Tile bloque le pathing
///
    bool bloquante();
    
private:
    int id, decalage_hauteur_image;
    bool bloquante_;
    Texture *texture;
    
public:
    static const int hauteurTile = 88;
};

}

#endif // TILETEMPLATE_HPP
