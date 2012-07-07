#include "cce/AnimationTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce {

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

void AnimationTemplate::makeAnimation(thor::Animator<sf::Sprite,string> *animptr)  const{

    thor::FrameAnimation *franim = new thor::FrameAnimation;
    //6 = getTexture().width / largeurFrame
    for (unsigned int i = debut; i < fin; ++i)
        franim->addFrame(1.f, sf::IntRect(rect_largeur*i, num_Animation*rect_hauteur, rect_largeur,  rect_hauteur));

    // Register animations with their corresponding durations
    animptr->addAnimation(nom, *franim, sf::seconds(temps));
    animptr->playAnimation(nom, true);
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
