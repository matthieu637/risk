#include "cli/Unit.hpp"
#include "bib/Logger.hpp"


namespace cli {

  Unit::Unit()
  {

  }
  
  void Unit::setUnitTemplate(cce::UnitTemplate *ut){
	unitTemplate = ut;//met a jour les caractéristiques de l'unité
	setTexture(ut->getTexture());//met a jour l'image de l'unité
	animation = ut->getAnimation();
	anim = cce::Animation();
	anim.makeAnimation();
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

}