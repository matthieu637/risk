#include "cce/Repere.hpp"
#include "bib/Logger.hpp"
#include "cce/Tile.hpp"

using sf::Vector2f;
using cce::Tile;

namespace cce {

Repere::Repere(int x, int y):tiles(x*y)
{
    largeur = x;
    hauteur = y;
    nbTiles = x * y;
    nbTiles_sans_derniere_ligne = nbTiles - largeur;
    
    
    setTile(Univers::getInstance()->getTileTemplate(1000000000), 0, 0);
    setTile(Univers::getInstance()->getTileTemplate(1000000000), 0, 5);
    setTile(Univers::getInstance()->getTileTemplate(1000000001), 10, 5); 
}

Repere::~Repere()
{

}

Tile& Repere::getTile (const int x, const int y)
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

int Repere::getIndice(int x, int y) const {

    int indice = 2*largeur * y/h_tile + x/l_tile;
    int x_rect = x % l_tile, y_rect = y % h_tile;

    if (y_rect <= h_tile_demi ) {
        if (x_rect <= l_tile_demi) {
            if ((h_tile_demi - y_rect) > (float)(h_sur_l * x_rect))
                //triangle haut gauche
                if (indice >= largeur) //ne pas déborder du tableau
                    indice -= largeur + 1;
        }
        else if ((int) y > - (float)( h_sur_l*(x - l_tile_demi)))
            //triangle haut droite
            if (indice >= largeur) //ne pas déborder du tableau
                indice -= largeur;
    }
    else if (x_rect <= l_tile_demi) {
        if ((int)(h_tile_demi - y) < -(float)(h_sur_l * x))
            //triangle bas gauche
            if (indice <= nbTiles_sans_derniere_ligne) //ne pas déborder du tableau
                indice += largeur - 1;
    }
    else if (h_tile - y < (float)(h_sur_l *(x-l_tile_demi)))
        //triangle bas droite
        if (indice <= nbTiles_sans_derniere_ligne) //ne pas déborder du tableau
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

    for(int indice_ligne= indice_debut ; indice_ligne < nbTileHauteur*2 ; indice_ligne++)
        for(int indice_colonne= 0; indice_colonne < nbTileLargeur ; indice_colonne++)
            target.draw(tiles[indice_ligne*largeur + indice_colonne], states);
}


}
