#include "edt/Repere.hpp"
#include "cce/Tile.hpp"
#include "cce/TileTemplate.hpp"

namespace edt{

Repere::Repere(int x, int y)
{
    largeur = x;
    hauteur = y;
    nbTiles = x * y;
    nbTiles_sans_derniere_ligne = nbTiles - largeur;
}

Repere::~Repere()
{

}

void Repere::setTile(cce::TileTemplate *_tt, const int x, const int y)
{
    int x_tile, y_tile;
    int i = getIndice(x, y);
    Tile *t = &tiles[i];
    t->setTemplate(_tt);

    y_tile = i/largeur - 1;
    y_tile *= h_tile_demi;
    //x_tile decale pour une ligne sur 2
    x_tile = l_tile * (i%largeur) + (y_tile%2) * l_tile_demi;


    t->setPosition(x_tile,y_tile);
}

void Repere::unsetTile(const int x, const int y)
{
  getTile(x, y).unsetTemplate();
}

void Repere::redimensionner(const int x, const int y)
{
    int i, j;
    vector<Tile> tiles_new(x*y);
    
    
    if(hauteur <= y)
      if(largeur <= x)
	for (j=0; j<hauteur; j++)
	  for(i=0; i<largeur; i++)
	    tiles_new[j*x + i] = tiles[j*largeur + i];
      else
	for (j=0; j<hauteur; j++)
	  for(i=0; i<x; i++)
	    tiles_new[j*x + i] = tiles[j*largeur + i];
    else
      if(largeur <= x)
	for (j=0; j<y; j++)
	  for(i=0; i<largeur; i++)
	    tiles_new[j*x + i] = tiles[j*largeur + i];
      else
	for (j=0; j<y; j++)
	  for(i=0; i<x; i++)
	    tiles_new[j*x + i] = tiles[j*largeur + i];
    
    largeur = x;
    hauteur = y;
    nbTiles = x * y;
    nbTiles_sans_derniere_ligne = nbTiles - largeur;
    tiles = tiles_new;
}

}