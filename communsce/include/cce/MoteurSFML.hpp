#ifndef CCE_MOTEURSFML_HPP
#define CCE_MOTEURSFML_HPP


///
///\file MoteurSFML.hpp
///\brief Contient toutes la gestion de SFML
///\author matthieu
///

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "bib/Logger.hpp"


namespace cce {

using sf::RenderWindow;
using sf::View;

class MoteurSFML
{

public:
    MoteurSFML(const string &nomFenetre): fenetre(sf::VideoMode::getDesktopMode(), nomFenetre),camera(sf::FloatRect()),camera2(sf::FloatRect())
    {
        LOG_INFO("Chargement d'une fenetre " << fenetre.getSize().x << "x" << fenetre.getSize().y);
        fenetre.setFramerateLimit(60);
        fenetre.setMouseCursorVisible(false);

        camera2.setSize(sf::Vector2f(500,500));
        camera2.setCenter(sf::Vector2f(1000,1000));
	camera2.setViewport(sf::FloatRect(0.f, 0.7f, 0.2f, 1.f));
        camera2.zoom(4);
    }


///
///\brief Méthode générale du rendu graphique
///
    template<class T, class U>
    void render(const T& drawable, U* gui_) {
        fenetre.clear();
        //camera.setViewport(sf::FloatRect(1,1,1,1));
        fenetre.setView(camera);

        fenetre.pushGLStates();
        fenetre.draw(drawable);

        fenetre.setView(camera2);
        fenetre.draw(drawable);
        fenetre.popGLStates();

        gui_->dessiner();

        fenetre.display();
    }

///
///\brief Fenetre pricipale SFML
///
    RenderWindow* getFenetre() {
        return &fenetre;
    }

///
///\brief Camera
///
    View* getView() {
        return &camera;
    }

private:
    RenderWindow fenetre;
    View camera,camera2;
};

}

#endif // CCE_MOTEURSFML_HPP

