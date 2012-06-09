#include <map>
#include "cce/ImageManager.hpp"

namespace cce {

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

sf::Texture* ImageManager::creer_ressource(const std::string& path, bool *succes)
{

    sf::Texture* texture = new sf::Texture;

    if(texture->loadFromFile( path )){
        *succes = true;
        return texture;
    }
    else{
         *succes = false;
         return NULL;
    }
}

} /* End of namespace cce */