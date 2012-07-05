#include "cli/Damier.hpp"
#include "cli/Unit.hpp"
#include "cli/Joueur.hpp"
#include "bib/Logger.hpp"

using namespace cli;

Damier::Damier(int largeurRepere, int hauteurRepere)
{
    nb_colonnes = largeurRepere/size_square_damier + 1;
    nb_lignes = hauteurRepere/size_square_damier + 1;
    
    damier = new vector< vector< set<Unit*>* > *>(nb_lignes);
    for(int i=0; i<nb_lignes; i++){
      damier->at(i) = new vector<set<Unit*>*>(nb_colonnes);
      for(int j=0; j<nb_colonnes; j++)
	damier->at(i)->at(j) = new set<Unit*>();
    }
}

Damier::~Damier()
{

}

void Damier::addUnit(Unit* u)
{
    int ligne = u->getSocleCenterGlobal().y / size_square_damier;
    int colonne = u->getSocleCenterGlobal().x / size_square_damier;
    
    getSquare(ligne,colonne)->insert(u);
}

void Damier::removeUnit(Unit* u)
{
    int ligne = u->getSocleCenterGlobal().y / size_square_damier;
    int colonne = u->getSocleCenterGlobal().x / size_square_damier;
    
    getSquare(ligne,colonne)->erase(u);
}

Unit* Damier::getUnit(sf::Vector2f position)
{
    int a;
    set<Unit*>::reverse_iterator it;
    
    //on fouille dans le carré qui contient la position, et ceux autour.
    int ligne_max = position.y / size_square_damier + 1;
    int colonne_max = position.x / size_square_damier + 1;
    int ligne_min = ligne_max - 2;
    int colonne_min = colonne_max - 2;
    
    if(ligne_max >= nb_lignes)
      ligne_max = nb_lignes - 1;
    if(colonne_max >= nb_colonnes)
      colonne_max = nb_colonnes - 1;
    if(ligne_min < 0)
      ligne_min = 0;
    if(colonne_min < 0)
      colonne_min = 0;
    
    for(int i = ligne_max; i >= ligne_min; i--)
      for(int j = colonne_max; j >= colonne_min; j--)
	for(it = getSquare(i,j)->rbegin(); it != getSquare(i,j)->rend(); it++)
	  if((*it)->getGlobalBounds().contains(position)) {
	    a = (*it)->getTexture()->copyToImage().getPixel(position.x - (*it)->getPosition().x, position.y - (*it)->getPosition().y).a;
	    if(a > 122) //pixel transparent? Permet de détecter véritablement l'unité cliquée lorsqu'elles sont superposées
	      return *it;
	  }
    return nullptr;
}

Unit* Damier::closestEnemyInRange(int range, sf::Vector2f position, Joueur* j)
{
    Unit* u = nullptr;
    int sizeRect = range*2;
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(position.x - range, position.y - range), sf::Vector2f(sizeRect, sizeRect));
    list<Unit*> liste = getUnitsInRect(&rect);
    
    if(liste.empty())
      return nullptr;
    
    float distance_actuelle = range, new_distance;
    list<Unit*>::iterator it;
    sf::Vector2f distance;
    
    for(it = liste.begin(); it != liste.end(); it++){
      if(((*it)->getOwner() != nullptr && j->isAllied((*it)->getOwner()->getNumber())) || (*it)->isDead()) // joueur allié (ou soi) ou unité morte
	continue;
      
      distance = position - (*it)->getPosition();
      new_distance = sqrt(distance.x * distance.x + distance.y * distance.y);
      
      if(new_distance > range) // hors de portée
	continue;
      
      if(new_distance < distance_actuelle){ // unité plus proche
	  u = *it;
	  distance_actuelle = new_distance;
      }
    }
    return u;
}

list<Unit*> Damier::getUnitsInRect(sf::FloatRect* rectangleSelection)
{
    list<Unit*> liste;
    set<Unit*>::iterator it;
    
    //on fouille dans les carrés qui contiennent le rectangle.
    int ligne_max = (rectangleSelection->top + rectangleSelection->height) / size_square_damier;
    int colonne_max = (rectangleSelection->left + rectangleSelection->width) / size_square_damier;
    int ligne_min = rectangleSelection->top / size_square_damier;
    int colonne_min = rectangleSelection->left / size_square_damier;
    
    if(ligne_max >= nb_lignes)
      ligne_max = nb_lignes - 1;
    if(colonne_max >= nb_colonnes)
      colonne_max = nb_colonnes - 1;
    if(ligne_min < 0)
      ligne_min = 0;
    if(colonne_min < 0)
      colonne_min = 0;
    
    for(int i = ligne_max; i >= ligne_min; i--)
      for(int j = colonne_max; j >= colonne_min; j--)
	for(it = getSquare(i,j)->begin(); it != getSquare(i,j)->end(); it++)
	  if(rectangleSelection->contains((*it)->getSocleCenterGlobal())) 
	    liste.push_back(*it);
    
    return liste;
}

bool Damier::collision(Unit* u, sf::Vector2f position) //optimiser avec une fonction collisionUnit (les decors sont fixes pour le pathfinding)
{
    sf::Vector2f distance;
    float d_rad = u->getSelectionCircle()->getRadius();
    float it_rad;
    
    //on fouille dans le carré qui contient la position, et ceux autour.
    int ligne_max = position.y / size_square_damier + 1;
    int colonne_max = position.x / size_square_damier + 1;
    int ligne_min = ligne_max - 2;
    int colonne_min = colonne_max - 2;
    
    if(ligne_max >= nb_lignes)
      ligne_max = nb_lignes - 1;
    if(colonne_max >= nb_colonnes)
      colonne_max = nb_colonnes - 1;
    if(ligne_min < 0)
      ligne_min = 0;
    if(colonne_min < 0)
      colonne_min = 0;
    
    set<Unit*>::iterator it;
    for(int i = ligne_max; i >= ligne_min; i--)
      for(int j = colonne_max; j >= colonne_min; j--)
	for(it = getSquare(i,j)->begin(); it != getSquare(i,j)->end(); it++) {
	  if((*it) == u)
	    continue;
	  distance = position - (*it)->getSocleCenterGlobal();
	  it_rad = (*it)->getSelectionCircle()->getRadius();
	  if(sqrt(distance.x * distance.x + distance.y * distance.y) < d_rad + it_rad)
	    return true;
    }
    return false;
}

set<Unit*>* Damier::getSquare(int ligne, int colonne)
{
  return damier->at(ligne)->at(colonne);
}