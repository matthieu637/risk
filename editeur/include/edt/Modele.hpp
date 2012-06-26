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


	void deleteTile(int x, int y);
	
///
///\brief sauvegarde une carte 
///
	string saveCarte(const string & chemin);

///
///\brief Choisir la palette
///

    void selectPalette(palette_type p);


///
///\brief Ajoute une region au pays actuellement sélectionné
///\param nom: nom de la region
///
    void addRegion(string nom);
    
    void moveScrollVert(float pos, float size);
    void moveScrollHori(float pos, float size);

  private:
      Repere * getRepere();

  private:
    int cameraOrigineX, cameraOrigineY;
    float coeff_zoom;
    bool tile, decor, region;
    string current_pays;
    cce::TileTemplate * tt;
    cce::DecorTemplate * dt;
    list < cce::Vue * >::iterator it;
};

}
#endif	// MODELEEDITEUR_HPP