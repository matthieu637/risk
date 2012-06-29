#include "cce/Animation.hpp"

namespace cce{
    
 Animation::Animation(AnimationTemplate *animTemplate){
      animationTemplate = animTemplate;
    
  }
  
  void Animation::makeAnimation(){

    thor::FrameAnimation franim;
    //6 = getTexture().width / largeurFrame 
    for (unsigned int i = 0; i < 6; ++i)
	 franim.addFrame(1.f, sf::IntRect(animationTemplate->getRect_largeur()*i, animationTemplate->getNum_Animation()*animationTemplate->getRect_hauteur(), animationTemplate->getRect_largeur(),  animationTemplate->getRect_hauteur()));
	 
    // Register animations with their corresponding durations
      anim.addAnimation(animationTemplate->getNom(), franim, sf::seconds(animationTemplate->getTemps().f));  
      anim.playAnimation(animationTemplate->getNom(), true);
  }
  
  AnimationTemplate* Animation::getTemplate(){
    return animationTemplate;
  }
  
  
}