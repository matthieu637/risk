#include "cli/Unit.hpp"
#include <cli/BastonManager.hpp>
#include "bib/Logger.hpp"
#include <cmath>
#include <stdlib.h>
#include <time.h>

namespace cli {

Unit::Unit()
{
    current_order = stop;
}

void Unit::setUnitTemplate(cce::UnitTemplate *ut){
      unitTemplate = ut;//met a jour les caractéristiques de l'unité
      setTexture(ut->getTexture());//met a jour l'image de l'unité
      animation = ut->getAnimation();
      unitTemplate = ut;
      current_hp = ut->getHP();
// 	thor::FrameAnimation moveUp;
// 	//moveUp.addFrame(1.f, sf::IntRectanimation.playAnimation("moveUp",true);(0, 0, ut->getTexture()->getSize().x/6, getTexture()->getSize().y/4));
// 	 for (unsigned int i = 0; i < 6; ++i)
// 	    moveUp.addFrame(1.f, sf::IntRect(47*i, 0, 47, 64));
// 	 
//     // Register animations with their corresponding durations
//       animation.addAnimation("moveUp", moveUp, sf::seconds(0.4f));  
//       animation.playAnimation("moveUp", true);
}


void Unit::setId(int id){
    setUnitTemplate(cce::Univers::getInstance()->getUnitTemplate(id));
}

order Unit::getOrder()
{
    return current_order;
}

void Unit::orderMove(sf::Vector2i point)
{
    destination = sf::Vector2f(point);
    current_order = order::move;
}

void Unit::orderFollow(Unit* to_follow)
{
    if(this == to_follow)
      current_order = stop;
    target_unit = to_follow;
    current_order = follow;
    distance_min_follow = getSelectionCircle()->getRadius() + target_unit->getSelectionCircle()->getRadius() + 50;
}

void Unit::applyOrder()
{
    switch(current_order){
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
    }
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
	current_order = order::stop;
    }
    else
      deplacement = to_go / (distance / speed); // distance parcourue déterminée en fonction de la speed
    move(deplacement.x, deplacement.y);
}

void Unit::attaquer()
{
    float range = unitTemplate->getRange();
    float speed = unitTemplate->getMoveSpeed();
    
    sf::Vector2f to_go = destination - socleGlobal; // vector jusqu'à destination
    float distance = sqrt(to_go.x * to_go.x + to_go.y * to_go.y); //distance à parcourir (pythagore)
    
    if(distance > range){ // pas à portée
      deplacement = to_go / (distance / speed); // distance parcourue déterminée en fonction de la speed
      move(deplacement.x, deplacement.y); // on avance vers la cible
    }
    
    else // à portée
      if(this->attaque_prete){
	target_unit->takeDamages(unitTemplate->getDamageType(), rollDamage());
    }
}

void Unit::takeDamages(cce::damage_type type_degat, int degats)
{
    float coeff_reduction = BastonManager::getInstance()->reduction_degats(unitTemplate->getDefenseType(),type_degat);
    float calcul_real_dmg = coeff_reduction * (degats - unitTemplate->getDefence()); 
    ///Si les dégats sont inférieurs à 1 alors on définit les dégats subits à 1
    if(calcul_real_dmg<1){
      calcul_real_dmg = 1;
    }
    current_hp -= calcul_real_dmg;
}

int Unit::rollDamage()
{
    srand(time(NULL));
    int degats_range = (unitTemplate->getDamageMax() - unitTemplate->getDamageMin() + 1);
    int degats_bonus = rand() % degats_range;
    return unitTemplate->getDamageMin() + degats_bonus;
}

}