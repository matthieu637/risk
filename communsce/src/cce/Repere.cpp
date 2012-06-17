#include "cce/Repere.hpp"
#include "bib/Logger.hpp"
#include "cce/Tile.hpp"

using sf::Vector2f;
using cce::Tile;

namespace cce {

Repere::Repere()
{
  
}

Repere::~Repere()
{

}

Tile& Repere::getTile (const int x, const int y)
{
    return tiles[getIndice(x, y)];
}

std::pair <int, int> Repere::getCoordonnees(int indice)
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

int Repere::getIndice(int x, int y) const {
    if (x<0 || y<0 || x>largeur_pixels || y>hauteur_pixels)
      return -1;

    int indice = largeur_double * (y/h_tile) + x/l_tile;
    float x_rect = x % l_tile, y_rect = y % h_tile; //coord du clic à l'intérieur du rectangle de la tile
    
    float demi_h_sur_demi_l = ((float)h_tile_demi/(float)l_tile_demi);

    if (y_rect <= h_tile_demi ) {
        if (x_rect <= l_tile_demi) {
            if (y_rect < h_tile_demi - demi_h_sur_demi_l * x_rect)
                //triangle haut gauche
                if (indice >= largeur) //ne pas déborder du tableau
                    indice -= largeur + 1;
        }
        else if (y_rect < demi_h_sur_demi_l * (x_rect - (float)l_tile_demi))
		//triangle haut droite
		if (indice >= largeur) //ne pas déborder du tableau
		    indice -= largeur;
    }
    else if (x_rect <= l_tile_demi) {
	    if (y_rect - h_tile_demi > demi_h_sur_demi_l * x_rect)
		//triangle bas gauche
		if (indice <= nbTiles_sans_derniere_ligne) //ne pas déborder du tableau
		    indice += largeur - 1;
	  }
	else if (y_rect - h_tile_demi > h_tile_demi - demi_h_sur_demi_l * (x_rect - (float)l_tile_demi))
		//triangle bas droite
		if (indice < nbTiles_sans_derniere_ligne) //ne pas déborder du tableau
		    indice += largeur;

    return indice;
}

void Repere::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Récupere la taille de l'écran et le centre de la vue
    const Vector2f centre =  target.getView().getCenter();
    const Vector2f taille =  target.getView().getSize();

    //cherche le point en haut à gauche de l'écran
    int gauche = centre.x - taille.x/2;
    int haut = centre.y - taille.y /2;

    //trouve sa tile
    int indice_debut = getIndice(gauche, haut);
    if (indice_debut - largeur >=0 ) //dessine 1 tile plus haut si possible
        indice_debut -= largeur;
    if (indice_debut % largeur > 0 ) //dessine 1 tile plus à gauche si possible
        indice_debut--;

    //trouve le nombre de tile en largeur et en hauteur à afficher
    int nbTileLargeur = (taille.x / l_tile) + 3;
    int nbTileHauteur = (taille.y / h_tile) + 3;


    //si la zone de vue est plus grande que la carte
    if ( indice_debut%largeur + nbTileLargeur >= largeur ) //reduit la largeur
        nbTileLargeur = largeur - indice_debut%largeur;
    if ( indice_debut/largeur + nbTileHauteur*2 >= hauteur) { //réduit la hauteur
        nbTileHauteur = (hauteur - (indice_debut/largeur))/2;
    }
/*
    for(int indice_ligne= indice_debut ; indice_ligne < nbTileHauteur*2 ; indice_ligne++)
        for(int indice_colonne= indice_debut; indice_colonne < indice_debut + nbTileLargeur ; indice_colonne++)
            target.draw(tiles[indice_ligne*largeur + indice_colonne], states);
    */
    for(int i=0;i<nbTiles;i++)
       target.draw(tiles[i], states);

}


}
