#include "cce/AnimationTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce{

AnimationTemplate::AnimationTemplate()
{
  
}


AnimationTemplate::AnimationTemplate(string n, int num,int deb,int end,float hauteur, float largeur, float tps)
{
  nom = n;
  num_Animation = num;
  debut = deb;
  fin = end;
  rect_hauteur = hauteur;
  rect_largeur = largeur;
  temps = tps;
}

thor::Animator<sf::Sprite, std::string>* AnimationTemplate::getAnimathor(){
    return &animathor; 
 }
 

AnimationTemplate::~AnimationTemplate()
{

}


string AnimationTemplate::getNom()
{
  return nom;
}

int AnimationTemplate::getNum_Animation()
{
  return num_Animation;
}

int AnimationTemplate::getDebut()
{
  return debut;
}

int AnimationTemplate::getFin()
{
  return fin;
}

float AnimationTemplate::getTemps()
{
  return temps;
}

float AnimationTemplate::getRect_largeur()
{
  return rect_largeur;
}

float AnimationTemplate::getRect_hauteur()
{
  return rect_hauteur;
}
}