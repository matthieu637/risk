#ifndef REPERE_HPP
#define REPERE_HPP

#include <vector>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "cce/Tile.hpp"


using sf::RenderTarget;
using boost::serialization::make_nvp;
using std::vector;


namespace cce {

class Univers;

class TileTemplate;

class Repere : public sf::Drawable
{

public:
///
///\brief Repere vide pour le créer via XML
///
    Repere();
    virtual ~Repere();

///
///\brief Renvoie la tile contenant le point (x,y)
///\param X : abcisse en pixels
///	  Y : ordonnee en pixels
///\return Retourne la tile correspondante
///
    Tile& getTile (const int x, const int y);

    int getLargeur() {
        return largeur;
    }
    int getHauteur() {
        return hauteur;
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        (void) version;
        ar & make_nvp("largeur", largeur);
        ar & make_nvp("hauteur", hauteur);

        ar & make_nvp("Tiles", tiles);
        boost::serialization::split_member(ar, *this, version);
    }

    template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
        (void) version;
        (void) ar;
    }

    template<class Archive>
    void load( Archive & ar, const unsigned int file_version ) {
        (void) file_version;
        (void) ar;
        nbTiles = largeur * hauteur;
        nbTiles_sans_derniere_ligne = nbTiles - largeur;

        for(int i=0; i<nbTiles; i++) {
            int y_tile, x_tile;
            y_tile = i/largeur - 1;
            y_tile *= h_tile_demi;
            //x_tile decale pour une ligne sur 2
            x_tile = l_tile * (i%largeur) + (y_tile%2) * l_tile_demi;
            tiles[i].init(x_tile, y_tile);
        }
    }

protected:
///
///\brief Retourne l'indice selon les coordonees en pixels
///\param x,y : coordonnes de la tile
///\return Retourne l'indice de la tile dans le tableau
///
    int getIndice(int x, int y) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
///
///\brief Tableau de tiles
///
    vector<Tile> tiles;
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
