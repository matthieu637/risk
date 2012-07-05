#include "cce/Animation.hpp"
#include <bib/Logger.hpp>

namespace cce{
 
 Animation::Animation(AnimationTemplate *animTemplate){
    animationTemplate = animTemplate;
  }
  
  void Animation::makeAnimation(){

    thor::FrameAnimation *franim = new thor::FrameAnimation;
    LOG_DEBUG(animationTemplate->getRect_largeur());
    LOG_DEBUG(animationTemplate->getNum_Animation()*animationTemplate->getRect_hauteur());
    LOG_DEBUG(animationTemplate->getRect_hauteur());
    //6 = getTexture().width / largeurFrame 
    for (unsigned int i = animationTemplate->getDebut(); i < animationTemplate->getFin(); ++i)
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