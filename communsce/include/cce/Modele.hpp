#ifndef MODELE_HPP
#define MODELE_HPP
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Carte.hpp"

namespace cce {

class Modele : public sf::Drawable
{

public:
    Modele();
    void update();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    Carte carte;
};

}

#endif // MODELE_HPP
