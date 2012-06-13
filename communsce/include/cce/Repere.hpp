#ifndef REPERE_HPP
#define REPERE_HPP

#include <math.h>
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
    Repere(int x, int y);
    virtual ~Repere();

///
///\brief Renvoie la tile contenant le point (x,y)
///\param X : abcisse en pixels
///	  Y : ordonnee en pixels
///\return Retourne la tile correspondante
///
    Tile& getTile (const int x, const int y);

///
///\brief Defini le TileTemplate d'une tile
///\param tt : TileTemplate à associer
///        x,y : coordonnes de la tile en pixels
///
    void setTile(TileTemplate *tt, const int x, const int y);

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
        ar & make_nvp("nbTiles", nbTiles);
        ar & make_nvp("nbTiles_sans_derniere_ligne", nbTiles_sans_derniere_ligne);
        ar & make_nvp("tiles", tiles);
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
        for(int i=0; i<hauteur; i++)
            for(int j=0; j<largeur; j++)
                tiles[i*largeur+j].init(i, j);
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
    static constexpr int h_tile = 88;
    static constexpr int l_tile = 158;
    static constexpr int h_tile_demi = 44;
    static constexpr int l_tile_demi = 79;
    static constexpr float h_sur_l = 88/158;
};

}

#endif // REPERE_HPP
