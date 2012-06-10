#ifndef MODELE_HPP
#define MODELE_HPP
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include "Carte.hpp"

namespace cce {

class Modele : public sf::Drawable
{

public:
    Modele();
    void update();
    void saveCarte(const std::string& chemin);
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    Carte carte;
};

}

#endif // MODELE_HPP
