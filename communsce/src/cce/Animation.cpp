#include "cce/Animation.hpp"
#include <bib/Logger.hpp>

namespace cce{
 
 Animation::Animation(){
  
 }
 
 Animation::Animation(AnimationTemplate *animTemplate){
      animationTemplate = animTemplate;
    
  }
  
  void Animation::makeAnimation(){

    thor::FrameAnimation *franim = new thor::FrameAnimation;
    //6 = getTexture().width / largeurFrame 
    for (unsigned int i = 0; i < 6; ++i)
	 franim->addFrame(1.f, sf::IntRect(animationTemplate->getRect_largeur()*i, animationTemplate->getNum_Animation()*animationTemplate->getRect_hauteur(), animationTemplate->getRect_largeur(),  animationTemplate->getRect_hauteur()));
	 
    // Register animations with their corresponding durations
      thor::Animator<sf::Sprite,string> *animptr = animationTemplate->getAnimathor();
      LOG_DEBUG(animationTemplate->getNom());
      animptr->addAnimation(animationTemplate->getNom(), *franim, sf::seconds(animationTemplate->getTemps()));  
      animptr->playAnimation(animationTemplate->getNom(), true);
  }
  
  AnimationTemplate* Animation::getTemplate(){
    return animationTemplate;
  }
  
  
}