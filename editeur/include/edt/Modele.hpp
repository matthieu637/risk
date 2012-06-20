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
///\brief Placer la tile actuellement sélectionné aux coordonées x,y pixels
///
	void placeTile(int x, int y);

///
///\brief Placer le decor actuellement sélectionné aux coordonées x,y pixels
///
	void placeDecor(int x, int y);

///
///\brief Supprimer le tile aux coordonées x,y pixels
///
	void deleteTile(int x, int y);

	void saveCarte(const string & chemin);

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
	string current_pays;
	cce::TileTemplate * tt;
	cce::DecorTemplate * dt;
    };

}
#endif	// MODELEEDITEUR_HPP