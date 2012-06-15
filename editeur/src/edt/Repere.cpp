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

pair <int, int> Repere::getCoordonnees(int indice)
{
    if(indice<0 || indice>nbTiles)
      return pair <int, int> (-1, -1);

    int x_tile, y_tile, ligne;
    ligne = (indice/largeur);
    y_tile = ligne * h_tile_demi;
    //x_tile decale pour une ligne sur 2
    x_tile = l_tile * (indice%largeur) + (ligne%2) * l_tile_demi;
    
    return pair <int, int>(x_tile, y_tile);
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