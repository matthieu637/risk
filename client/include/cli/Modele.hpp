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
class Joueur;
class CoucheDecor;
class Unit;

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
    void moveView(int dx, int dy, int cameraL, int cameraH);

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
///\brief Initier le déplacement de la selection d'unités vers le point mousePosition
///
    void moveUnitSelection(sf::Vector2i mousePosition);

///
///\brief Supprimer une unité de la mémoire, l'enlève également des collections où elle apparait.
///
    void deleteUnit(Unit* u);

///
///\brief unité ennemie au joueur j la plus proche de position dans le rayon range.
///
    Unit* closestEnemyInRange(int range, sf::Vector2f position, Joueur* j);
    
    void windowResized(int width, int height);
    
    void spawnUnit(int id, int x, int y, int joueur);
    
    void initSelection(int x, int y);
    
    void endSelection();
    void endSelectionShift();

    void moveSelection(int x, int y);   
    void removeSelection(int x, int y);
    
    void on_attack(sf::Vector2i mousePosition);
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    CoucheDecor* getCoucheDecor(){return (CoucheDecor*)carte->getCoucheDecor();}


    
  private:
    int cameraOrigineX, cameraOrigineY, player_number;
    bool selectionBool;
    float coeff_zoom;
    list <cce::Vue*>::iterator it;
    set<Unit*> selectionUnits;
    vector <Joueur> players;
    sf::Vector2f origineSelection;
    sf::RectangleShape* rectangleSelection;
    
    void removeUnitSelection(Unit* un);

    void addUnitSelection(Unit* un);
};

}
#endif	// MODELEEDITEUR_HPP