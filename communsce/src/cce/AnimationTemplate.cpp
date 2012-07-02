#include "cce/AnimationTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce{

AnimationTemplate::AnimationTemplate()
{
  
}


AnimationTemplate::AnimationTemplate(string n, int num,float hauteur, float largeur, float tps)
{
  nom = n;
  num_Animation = num;
  rect_hauteur = hauteur;
  rect_largeur = largeur;
  temps = tps;
}

void AnimationTemplate::loadAfterXML(int id)
{
//   this->id = id;
//   
//   //à supprimer pour ne pas charger tous les décors en mémoire
//   ImageManager::getInstance()->load_asset(id, path);
//   
//   texture = &ImageManager::getInstance()->get_asset(id);
//   initAnimation();
 
  
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