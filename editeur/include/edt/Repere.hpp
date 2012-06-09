#ifndef REPEREEDITEUR_HPP
#define REPEREEDITEUR_HPP

#include <cce/Repere.hpp>
#include <cce/Tile.hpp>

using cce::Tile;

namespace edt{

class Repere : public cce::Repere
{

public:
    Repere(int x, int y);
    virtual ~Repere();

///
///\brief Supprime la texture d'une tile
///\param x,y : coordonnes de la tile en pixels
///
    void unsetTile(const int x, const int y);
    
///
///\brief Redimensionne le repere
///\param x,y : taille du repere en tiles
///
    void redimensionner(const int x, const int y);
};

}

#endif // REPERE_HPP
