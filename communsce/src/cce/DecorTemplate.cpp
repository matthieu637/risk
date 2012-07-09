#include "cce/DecorTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce {

DecorTemplate::DecorTemplate()
{

}

void DecorTemplate::loadAfterXML(int id)
{
    this->id = id;

    //à supprimer pour ne pas charger tous les décors en mémoire
    ImageManager::getInstance()->load_asset(id, path);

    texture = &ImageManager::getInstance()->get_asset(id);
}


void DecorTemplate::initAnimation(thor::Animator<sf::Sprite,string> *animptr)
{
    if(mapAnimTemplate.size() > 1) {
        map<std::string,AnimationTemplate>::const_iterator it;
        for( it = mapAnimTemplate.begin(); it != mapAnimTemplate.end() ; it++)
            it->second.makeAnimation(animptr, it->first);
        animptr->playAnimation("static");
    }
}


DecorTemplate::~DecorTemplate()
{

}


Texture* DecorTemplate::getTexture()
{
    return texture;
}

int DecorTemplate::getID()
{
    return id;
}

bool DecorTemplate::bloquant()
{
    return bloquant_;
}

}

