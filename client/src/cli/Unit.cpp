#include "cli/Unit.hpp"
#include "bib/Logger.hpp"
#include <cmath>

namespace cli {

Unit::Unit()
{
    current_order = stop;
}


  
  
  void Unit::setUnitTemplate(cce::UnitTemplate *ut){
	unitTemplate = ut;//met a jour les caractéristiques de l'unité
	setTexture(ut->getTexture());//met a jour l'image de l'unité
	//animation = ut->getAnimation();
	anim = cce::Animation(ut->getMapTemplate());
	anim.makeAnimation();//commande qui fait bugger! a toi de jouer gourou
	 // unitTemplate = ut;
// 	thor::FrameAnimation moveUp;
// 	//moveUp.addFrame(1.f, sf::IntRectanimation.playAnimation("moveUp",true);(0, 0, ut->getTexture()->getSize().x/6, getTexture()->getSize().y/4));
// 	 for (unsigned int i = 0; i < 6; ++i)
// 	    moveUp.addFrame(1.f, sf::IntRect(47*i, 0, 47, 64));
// 	 
//     // Register animations with their corresponding durations
//       animation.addAnimation("moveUp", moveUp, sf::seconds(0.4f));  
//       animation.playAnimation("moveUp", true);
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
    followed_unit = to_follow;
    current_order = follow;
    distance_min_follow = getSelectionCircle()->getRadius() + followed_unit->getSelectionCircle()->getRadius() + 50;
}

void Unit::applyOrder()
{
    switch(current_order){
      case order::move:
	deplacer();
	break;
      case order::follow:
	destination = followed_unit->getSocleCenterGlobal();
	deplacer();
	break;
    }
}

  void Unit::setId(int id){
      setUnitTemplate(cce::Univers::getInstance()->getUnitTemplate(id));
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


}