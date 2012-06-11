#ifndef MODELE_HPP
#define MODELE_HPP

///
///\file Modele.hpp
///\brief Modele général de l'application
///\author matthieu
///

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include "Carte.hpp"

namespace cce {
  
class MoteurSFML;

class Modele : public sf::Drawable
{

public:
    Modele();
///
///\brief engine doit être le même que celui de la vue et du controle
///
    void init(MoteurSFML* engine);
    
///
///\brief Calculs à effectuer par le modèle à chaque pas de boucle
///
    void update();
    void saveCarte(const std::string& chemin);
    
///
///\brief Bouger la camera
///
    void moveView(int dx, int dy);
    
protected:
///
///\brief Méthode d'affichage SFML
///
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    MoteurSFML* engine;
    Carte carte;
};

}

#endif // MODELE_HPP
