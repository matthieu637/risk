#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "cce/AnimationTemplate.hpp"
#include <Thor/Animation.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace cce{
  class Animation 
  {
    public:
      Animation(AnimationTemplate *animTemplate);
      AnimationTemplate* getTemplate();
      void makeAnimation();
    
    private :
	AnimationTemplate *animationTemplate;
  };

}
#endif // ANIMATION_HPP