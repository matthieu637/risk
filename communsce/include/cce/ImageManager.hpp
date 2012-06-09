///
///\file ImageManager.hpp
///\brief Gere les fichiers image.
///\author Aymeric
///

#ifndef CCE_IMAGEMANAGER_H
#define CCE_IMAGEMANAGER_H

#include <SFML/Graphics.hpp>
#include "bib/AssetManager.hpp"
#include "bib/Singleton.hpp"

namespace cce {

class ImageManager : public bib::AssetManager<sf::Texture>, public bib::Singleton<ImageManager>
{
    friend class bib::Singleton<ImageManager>;

    private:
        ImageManager();
        virtual ~ImageManager();
    private:
        sf::Texture* creer_ressource(const std::string& path, bool *succes);
};

} /* End of namespace cce */

#endif // CCE_IMAGEMANAGER_H