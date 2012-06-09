#include "../../include/edt/Repere.hpp"

namespace edt{

Repere::Repere(int x, int y) : cce::Repere(x, y)
{

}

Repere::~Repere()
{

}

void Repere::unsetTile(const int x, const int y)
{
  getTile(x, y).unsetTemplate();
}

void Repere::redimensionner(const int x, const int y)
{
    int i, j;
    Tile* tiles_new = new Tile[x*y];
    
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