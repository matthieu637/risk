#ifndef CCE_MOTEURSFML_HPP
#define CCE_MOTEURSFML_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "bib/Logger.hpp"
#include "Modele.hpp"

namespace cce {

using sf::RenderWindow;
using sf::View;

class MoteurSFML
{

public:
    MoteurSFML(): fenetre(sf::VideoMode(1440,900), "*** Editeur Risk ***"),camera(sf::FloatRect(0,0,1440,900))
    {
	LOG_INFO("Chargement d'une fenetre " << 1440 << "x" << 900);
        fenetre.setFramerateLimit(60);
    }

    template<class T>
    void render(const T& drawable) {
        fenetre.clear();
        //fenetre.setView(camera);

        fenetre.pushGLStates();
        fenetre.draw(drawable);
        fenetre.popGLStates();

        fenetre.display();
    }

private:
    RenderWindow fenetre;
    View camera;
};

}

#endif // CCE_MOTEURSFML_HPP
