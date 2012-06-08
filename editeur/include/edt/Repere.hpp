#ifndef REPERE_HPP
#define REPERE_HPP

#include <cce/Repere.hpp>

using cce::Tile;

namespace edt{

class Repere : public cce::Repere
{

public:
    Repere();
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
