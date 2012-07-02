#include "edt/Repere.hpp"
#include "cce/Tile.hpp"
#include "cce/TileTemplate.hpp"

namespace edt{

Repere::Repere(int x, int y) : cce::Repere()
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
    int i = getIndice(x, y);
    if(i == -1)
      return;
    
    Tile *t = &tiles[i];
    t->setTemplate(_tt);
    
    pair <int, int> coord(getCoordonnees(i));
    t->setPosition(coord.first,coord.second);
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
    nbTiles = largeur * hauteur;
    nbTiles_sans_derniere_ligne = nbTiles - largeur;
    largeur_pixels = largeur * l_tile;
    hauteur_pixels = hauteur * h_tile_demi;
    largeur_double = largeur * 2;
    tiles = tiles_new;
}

}