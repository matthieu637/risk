#ifndef MODELE_HPP
#define MODELE_HPP

///
///\file Modele.hpp
///\brief Modele général de l'application
///\author matthieu, aymeric
///

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include <list>
#include "cce/Carte.hpp"
#include <CEGUI/CEGUIString.h>

namespace cce {
  
class MoteurSFML;
class Vue;
  
class Modele : public sf::Drawable
{

public:
    Modele();
    ~Modele();
    
///
///\brief Calculs à effectuer par le modèle à chaque pas de boucle
///
    void update();
    
///
///\brief Ajouter une vue
///
    void addVue(Vue* vue);
    
 ///
///\brief ouvre une carte
///
    virtual string openCarte(const string& chemin);
    
    Carte* getCarte();
    
protected:
///
///\brief Méthode d'affichage SFML
///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
protected:
    Carte* carte;
    std::list<Vue*> vues;
    
};

}

#endif // MODELE_HPP
