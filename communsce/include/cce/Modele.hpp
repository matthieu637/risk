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
#include <vector>
#include "Carte.hpp"

namespace cce {
  
class MoteurSFML;
class Vue;
  
class Modele : public sf::Drawable
{

public:
    Modele();
    ~Modele();
///
///\brief engine doit être le même que celui de la vue et du controle
///
    void init(MoteurSFML* engine);
    
///
///\brief Calculs à effectuer par le modèle à chaque pas de boucle
///
    void update();
    
///
///\brief Ajouter une vue
///
    void addVue(Vue* vue);
    
///
///\brief Changer les coordonées par (dx,dy) de la caméra selon sa largeur et sa hauteur.
///
    void moveView(int dx, int dy, int cameraX, int cameraY, int cameraL, int cameraH);
    
///
///\brief Ajuster le zoom en fonction du nombre de ticks scrollé et du champ couvert par la caméra.
///
    void zoom(int ticks);
    
    void saveCarte(const std::string& chemin);
    
protected:
///
///\brief Méthode d'affichage SFML
///
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    MoteurSFML* engine;
    Carte* carte;
    int cameraX, cameraY;
    vector<Vue> vues;
};

}

#endif // MODELE_HPP
