#include "cli/Unit.hpp"
#include "cli/BastonManager.hpp"
#include "bib/Logger.hpp"
#include <cmath>
#include "cli/Modele.hpp"
#include "cli/CoucheDecor.hpp"
#include "cli/Joueur.hpp"
#include <stdlib.h>
#include <time.h>

namespace cli {

   bool init = true;
Unit::Unit()
{
    current_order = stop;
    dead = false;
}

void Unit::animate(){  
  // Update animator and apply current animation state to the sprite
  cce::Decor::animate();
  /*
  animathor.update(frameClock.restart());
  animathor.animate(*this);
  */
}
  

Unit::~Unit(){
  
}
Unit::Unit(Modele* ma, Joueur* joueur)
{
    this->m = ma;
    current_order = stop;
    owner = joueur;
    distance_aggro = 500;
    dead = false;
}

void Unit::setUnitTemplate(cce::UnitTemplate *ut){
      unitTemplate = ut;//met a jour les caractéristiques de l'unité
      setTexture(ut->getTexture());//met a jour l'image de l'unité
      unitTemplate = ut;
      current_hp = ut->getHP();
      attaque_prete = true;
      ut->initAnimation(&animathor);

      
      
      if(init){
	//anim["anim1"]->makeAnimation(&animathor);
	init = false;
      }
}


order Unit::getOrder()
{
    return current_order;
}

void Unit::orderStop()
{
    current_order = order::stop;
    checkAggro();
}

void Unit::orderMove(sf::Vector2i point)
{
    destination = sf::Vector2f(point);
    current_order = order::move;
}

void Unit::orderFollow(Unit* to_follow)
{
    if(this == to_follow){
      orderStop();
      return;
    }
    if(current_order == order::follow || current_order == order::attack)
      target_unit->removeTraqueur(this);
    target_unit = to_follow;
    current_order = order::follow;
    target_unit->addTraqueur(this);
    distance_min_follow = getSelectionCircle()->getRadius() + target_unit->getSelectionCircle()->getRadius() + 50;
}

void Unit::orderAttack(Unit* to_attack)
{
    if(this == to_attack){
      orderStop();
      return;
    }
    if(current_order == order::follow || current_order == order::attack)
      target_unit->removeTraqueur(this);
    target_unit = to_attack;
    current_order = order::attack;
    target_unit->addTraqueur(this);
}

void Unit::applyOrder()
{
    switch(current_order){
      case order::stop:
	break;
      case order::move:
	deplacer();
	break;
      case order::follow:
	destination = target_unit->getSocleCenterGlobal();
	deplacer();
	break;
      case order::attack:
	attaquer();
	break;
      default:
	break;
    }
}

void Unit::setId(int id){
    setUnitTemplate(cce::Univers::getInstance()->getUnitTemplate(id));
}

void Unit::checkAggro()
{
    Unit* u = m->closestEnemyInRange(distance_aggro, getPosition(), owner);
    if(u != nullptr)
      orderAttack(u);
}

void Unit::deplacer()
{
    float speed = unitTemplate->getMoveSpeed();
    
    sf::Vector2f to_go = destination - socleGlobal; // vector jusqu'à destination
    float distance = sqrt(to_go.x * to_go.x + to_go.y * to_go.y); //distance à parcourir (pythagore)
    
    if(current_order == order::follow && distance < distance_min_follow)
      return;
    
    if(distance < speed){ //si la destination est à portée de speed
      deplacement = to_go; // on va jusqu'à destination
      if(current_order == order::move)
	orderStop();
    }
    else
      deplacement = to_go / (distance / speed); // distance parcourue déterminée en fonction de la speed
//     if(!m->getCoucheDecor()->collision(this, getSocleCenterGlobal() + deplacement)){
      //déplacement et tri dans l'arbre
      m->getCoucheDecor()->removeUnit(this);
      move(deplacement.x, deplacement.y);
      m->getCoucheDecor()->addUnit(this);
//     }
}

void Unit::attaquer()
{
    destination = target_unit->getSocleCenterGlobal();

    float range = unitTemplate->getRange();
    float speed = unitTemplate->getMoveSpeed();
    
    sf::Vector2f to_go = destination - socleGlobal; // vector jusqu'à destination
    float distance = sqrt(to_go.x * to_go.x + to_go.y * to_go.y); //distance à parcourir (pythagore)
    
    if(distance > range){ // pas à portée
      deplacement = to_go / (distance / speed); // distance parcourue déterminée en fonction de la speed
//       if(!m->getCoucheDecor()->collision(this, getSocleCenterGlobal() + deplacement)){
	//déplacement et tri dans l'arbre
	m->getCoucheDecor()->removeUnit(this);
	move(deplacement.x, deplacement.y);
	m->getCoucheDecor()->addUnit(this);
//       }
    }
    else // à portée
      if(this->attaque_prete)
	target_unit->takeDamages(unitTemplate->getDamageType(), rollDamage());
}

void Unit::takeDamages(cce::damage_type type_degat, int degats)
{
    float coeff_reduction = BastonManager::getInstance()->reduction_degats(unitTemplate->getDefenseType(),type_degat);
    float calcul_real_dmg = (unitTemplate->getDefence() * coeff_reduction) * degats; 
    ///Si les dégats sont inférieurs à 1 alors on définit les dégats subits à 1
    if(calcul_real_dmg<1){
      calcul_real_dmg = 1;
    }
    current_hp -= calcul_real_dmg;
    if(current_hp <= 0){ // mort
      dead = true;
      //on met les traqueurs en mode stop
      set<Unit*>::iterator it;
      for(it = traqueurs.begin(); it != traqueurs.end(); it++)
	(*it)->orderStop();
    }
}

bool Unit::isDead(){
  return dead;
}

int Unit::rollDamage()
{
    srand(time(NULL));
    int degats_range = (unitTemplate->getDamageMax() - unitTemplate->getDamageMin() + 1);
    int degats_bonus = rand() % degats_range;
    return unitTemplate->getDamageMin() + degats_bonus;
}

Joueur* Unit::getOwner(){
    return owner;
}

void Unit::addTraqueur(Unit* traqueur)
{
    traqueurs.insert(traqueur);
}

void Unit::removeTraqueur(Unit* traqueur)
{
    traqueurs.erase(traqueur);
}

}