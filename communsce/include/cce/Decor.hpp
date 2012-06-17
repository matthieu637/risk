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
    
///
///\brief Comparaison pour la position dans l'arbre
///\return True si ce decor vient avant d
///
    bool inferieurA(const Decor& d) const;
    
///
///\brief Changer la texture de l'objet (ajuste yCompare pour la position dans l'arbre)
///
    void setTexture(Texture* texture);

public:
    int yCompare;
    
private:
    DecorTemplate *dt;
};
    
bool operator<(Decor const &d1, Decor const &d2);

}
#endif // DECOR_HPP
