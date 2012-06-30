#include "cli/Unit.hpp"
#include "bib/Logger.hpp"

namespace cli {

  Unit::Unit()
  {
      current_order = hold;
  }
  
  void Unit::setUnitTemplate(cce::UnitTemplate *ut){
	unitTemplate = ut;//met a jour les caractéristiques de l'unité
	setTexture(ut->getTexture());//met a jour l'image de l'unité
	animation = ut->getAnimation();
	unitTemplate = ut;
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
  
void Unit::orderMove(sf::Vector2i point)
{
    //pour que les pieds arrivent au point cliqué
    sf::Vector2i point_socle(point.x - getLocalBounds().width/2, point.y - getLocalBounds().height * 3 / 4);
    destination = point_socle;
    current_order = order::move;
}

order Unit::getOrder()
{
    return current_order;
}

void Unit::applyOrder()
{
    switch(current_order){
      case order::move:
	deplacer();
	break;
    }
}

void Unit::deplacer()
{
    float speed = unitTemplate->getMoveSpeed();
    float x_to_go = destination.x - getPosition().x; //distance à parcourir x
    float y_to_go = destination.y - getPosition().y; //distance à parcourir y
    float x_to_go_abs = abs(x_to_go);
    float y_to_go_abs = abs(y_to_go);
    if(x_to_go_abs == 0)
	x_to_go = 0;
    if(y_to_go_abs == 0)
	y_to_go = 0;
    float distance = x_to_go_abs + y_to_go_abs; //distance à parcourir totale
    if (distance == 0){
	current_order = stop;
	return;
    }
    float dx = (x_to_go * speed) / distance;
    float dy = (y_to_go * speed) / distance;
    if(abs(dx) > x_to_go_abs)
      dx = x_to_go;
    if(abs(dy) > y_to_go_abs)
      dy = y_to_go;
    move(dx, dy);
}

}