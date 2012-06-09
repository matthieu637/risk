#ifndef REPERE_HPP
#define REPERE_HPP

#include <math.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "Tile.hpp"
#include "TileTemplate.hpp"

using sf::RenderTarget;

namespace cce{

class Repere
{

public:
    Repere(int x, int y);
    virtual ~Repere();
    
///
///\brief Renvoie la tile contenant le point (x,y)
///\param X : abcisse en pixels
///	  Y : ordonnee en pixels
///\return Retourne la tile correspondante
///
    Tile& getTile (const int x, const int y) const;

///
///\brief Defini le TileTemplate d'une tile
///\param tt : TileTemplate à associer
///        x,y : coordonnes de la tile en pixels
///
    void setTile(TileTemplate *tt, const int x, const int y);
    
    void dessiner(RenderTarget& cible);

public:
///
///\brief Retourne l'indice selon les coordonees en pixels
///\param x,y : coordonnes de la tile
///\return Retourne l'indice de la tile dans le tableau
///
    int getIndice(int x, int y) const;
///
///\brief Tableau de tiles
///
    Tile* tiles;
    int largeur;
    int hauteur;
    int nbTiles;
    int nbTiles_sans_derniere_ligne;
    const int h_tile = 88;
    const int l_tile = 158;
    const int h_tile_demi = 44;
    const int l_tile_demi = 79;
    const float h_sur_l = 88/158;
};

}

#endif // REPERE_HPP
