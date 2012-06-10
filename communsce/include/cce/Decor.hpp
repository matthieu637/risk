#ifndef DECOR_HPP
#define DECOR_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

using sf::Texture;
using sf::Sprite;

namespace cce{
  
class DecorTemplate;

class Decor : public Sprite
{

public:
    Decor(DecorTemplate *_dt, int x, int y);
    virtual ~Decor();
    
///
///\brief Retourne le Template de la tile
///\return Retourne le Template de la tile
///
    DecorTemplate* getTemplate() const;
    
    void setTexture(const Texture& texture, bool resetRect = false);
    
///
///\brief Comparaison pour la position dans l'arbre
///\return True si ce decor vient avant d2
///
    bool operator <(const Decor& d) const;

public:
    int yCompare;
    
private:
    DecorTemplate *dt;
};

}
#endif // DECOR_HPP
