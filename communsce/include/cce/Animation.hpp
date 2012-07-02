#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "cce/AnimationTemplate.hpp"
#include <Thor/Animation.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace cce{
  class Animation 
  {
    public:
      Animation();
      Animation(AnimationTemplate *animTemplate);
      AnimationTemplate* getTemplate();
      void makeAnimation();
    
    private :
	AnimationTemplate *animationTemplate;
	 thor::Animator<sf::Sprite, std::string> anim;
  };

}
#endif // ANIMATION_HPP