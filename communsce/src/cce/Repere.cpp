#include "cce/Repere.hpp"

using sf::Vector2f;
using cce::Tile;

namespace cce {
  
Repere::Repere(int x, int y)
{
  largeur = x;
  hauteur = y;
  nbTiles = x * y;
  nbTiles_sans_derniere_ligne = nbTiles - largeur;
  tiles = new Tile[nbTiles];
}

Repere::~Repere()
{

}

Tile& Repere::getTile (const int x, const int y) const
{
  return tiles[getIndice(x, y)];
}

void Repere::setTile(TileTemplate *tt, const int x, const int y)
{
  int x_tile, y_tile;
  int i = getIndice(x, y);
  Tile t = tiles[i];
  t.setTemplate(tt);
  
  y_tile = i/largeur;
  //x_tile decale pour une ligne sur 2
  x_tile = l_tile * i%largeur + y_tile%2 * l_tile_demi;
  
  t.setPosition(x_tile,y_tile);
}

void Repere::dessiner(RenderTarget& cible)
{
    Vector2f centre =  cible.getView().getCenter();
    const Vector2f taille =  cible.getView().getSize();

    int gauche = centre.x - taille.x/2;
    int haut = centre.y - taille.y /2;


    int indice_debut = getIndice(gauche, haut);
    if (indice_debut - largeur >=0 )
        indice_debut -= largeur;
    if (indice_debut % largeur > 0 )
        indice_debut--;
    int nbTileLargeur = (taille.x / 158) +3;
    int nbTileHauteur = (taille.y / 88) +3;


    if ( indice_debut%largeur + nbTileLargeur >= largeur )
        nbTileLargeur = largeur - indice_debut%largeur;
    if ( indice_debut/largeur + nbTileHauteur*2 >= hauteur) {
        nbTileHauteur = (hauteur - (indice_debut/largeur))/2 + 1;
        if (ceil((float)((hauteur - (indice_debut/largeur))/2.)) == (hauteur - (indice_debut/largeur))/2)
            indice_debut-= 2*largeur;
        else
            indice_debut -= largeur;
    }

    Tile *indice_ligne, *indice_colonne, *finLigne, *finColonne;

    finLigne = tiles + indice_debut + (nbTileHauteur*largeur*2);
    for (indice_ligne = tiles + indice_debut ; indice_ligne < finLigne ; indice_ligne+=largeur ) {
        finColonne = indice_ligne + nbTileLargeur;
        for (indice_colonne = indice_ligne; indice_colonne < finColonne ; indice_colonne++ ) 
            cible.draw(*indice_colonne);
    }
}

int Repere::getIndice(int x, int y) const{

  int indice = 2*largeur * y/h_tile + x/l_tile;
  int x_rect = x % l_tile, y_rect = y % h_tile;
  
  if (y_rect <= h_tile_demi )
    if (x_rect <= l_tile_demi){
      if ((h_tile_demi - y_rect) > (float)(h_sur_l * x_rect))
	//triangle haut gauche
	if (indice >= largeur) //ne pas déborder du tableau
	  indice -= largeur + 1;
    }
    else
      if ((int) y > - (float)( h_sur_l*(x - l_tile_demi)))
	//triangle haut droite
	if (indice >= largeur) //ne pas déborder du tableau
	  indice -= largeur;
  else
    if (x_rect <= l_tile_demi){
      if ((int)(h_tile_demi - y) < -(float)(h_sur_l * x))
	//triangle bas gauche
	if (indice <= nbTiles_sans_derniere_ligne) //ne pas déborder du tableau
	  indice += largeur - 1;
    }
    else
      if (h_tile - y < (float)(h_sur_l *(x-l_tile_demi)))
	//triangle bas droite
	if (indice <= nbTiles_sans_derniere_ligne) //ne pas déborder du tableau
	  indice += largeur;

  return indice;
}

}