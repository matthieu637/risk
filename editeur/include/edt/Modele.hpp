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

namespace edt {

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

///
///\brief Initialise le decor à déplacer
///\param x, y: coordonnees du decor à déplacer
///
    void setDecorMove(int x, int y);
    
///
///\brief Deplacer l'objet en x,y vers les coordonées x1,y1
///
    void moveDecor(int x1, int y1);
    
///
///\brief Placer l'objet actuellement sélectionné aux coordonées x,y pixels
///
    void placeObject(int x, int y);

///
///\brief Supprimer l'objet aux coordonées x,y pixels
///
    void deleteObject(int x, int y);

///
///\brief Changer le tileTemplate à placer par son id
///
    void setTileTemplate(int id);

///
///\brief Changer le decorTemplate à placer par son id
///
    void setDecorTemplate(int id);

///
///\brief Changer le pays sur lequel on opère
///
    void setCurrentPays(string nom);

///
///\brief Changer le decorTemplate à placer par son id
///
    void setSpawn(int x, int y);


    void deleteTile(int x, int y);
    
    void nouvelleCarte();
    
    void windowResized(int width, int height);

///
///\brief sauvegarde une carte 
///
    string saveCarte(const string & chemin);
    string saveCarte();
    string openCarte(const std::string & chemin);
    string getCurrentMap();
    
///
///\brief Choisir la palette
///
    void selectPalette(palette_type p);

///
///\brief Ajoute une region au pays actuellement sélectionné
///\param nom: nom de la region
///
    void addRegion(string nom);
    
    void moveScrollVert(float pos);
    void moveScrollHori(float pos);

  private:
      Repere * getRepere();

  private:
    int cameraOrigineX, cameraOrigineY;
    float coeff_zoom;
    palette_type palette;
    string current_pays;
    cce::TileTemplate * tt;
    cce::DecorTemplate * dt;
    list < cce::Vue * >::iterator it;
    string current_map;
    
};

}
#endif	// MODELEEDITEUR_HPP