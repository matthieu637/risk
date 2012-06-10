#ifndef CCE_CARTE_HPP
#define CCE_CARTE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "Repere.hpp"


namespace cce {

class Carte : public sf::Drawable
{

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Carte();
private:
    Repere repere;
};

}

#endif // CCE_CARTE_HPP
