#ifndef DECOR_HPP
#define DECOR_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "DecorTemplate.hpp"

using sf::Texture;
using sf::Sprite;

namespace cce{

class Decor : public Sprite
{

public:
    Decor(DecorTemplate *_dt, int x, int y);
    virtual ~Decor();
    
///
///\brief Retourne le Template de la tile
///\return Retourne le Template de la tile
///
    TileTemplate* getTemplate() const;
    
///
///\brief Redefinir les coordonnees en pixels
///
    void setCoordonnees(const int x, const int y);

private:
    DecorTemplate *dt;
    int x, y;
};

}
#endif // DECOR_HPP
