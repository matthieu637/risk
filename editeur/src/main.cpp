#include <iostream>
#include "cce/DaGame.hpp"
#include "cce/ImageManager.hpp"

using namespace cce;

int main()
{
    ImageManager::getInstance()->add_resource_directory("data/texture/");
    
    cce::DaGame game;
    game.gameloop();
    
    return EXIT_SUCCESS;
}
