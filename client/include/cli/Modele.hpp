#ifndef MODELEEDITEUR_HPP
#define MODELEEDITEUR_HPP

///
///\file Modele.hpp
///\brief Modele général de l'application
///\author matthieu, aymeric
///

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <cce/Modele.hpp>
#include <string>

using std::string;

namespace cli {

enum palette_type
{
    tiles, decors, regions, pays
};

class Vue;
class Repere;

class Modele:public cce::Modele {

public:
    Modele();
    ~Modele();

///
///\brief Calculs à effectuer par le modèle à chaque pas de boucle
///
    void update();

///
///\brief Changer les coordonées par (dx,dy) de la caméra selon sa largeur et sa hauteur.
///
    void moveView(int dx, int dy, int cameraX, int cameraY);

///
///\brief stocker le point d'origine de la caméra avant de commencer le déplacement par drag
///
    void setCamOrigine(int cameraX, int cameraY);

///
///\brief Ajuster le zoom en fonction du nombre de ticks scrollé et du champ couvert par la caméra.
///
    void zoom(int ticks);

///
///\brief Remettre le zoom à 0
///
    void resetZoom();
    
    void windowResized(int width, int height);

  private:
    int cameraOrigineX, cameraOrigineY;
    float coeff_zoom;
    list < cce::Vue * >::iterator it;
};

}
#endif	// MODELEEDITEUR_HPP