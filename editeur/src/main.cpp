#include <iostream>
#include "cce/DaGame.hpp"
#include "cce/ImageManager.hpp"

#include <iostream>
#include <cce/Tile.hpp>
#include <edt/Repere.hpp>
#include "cce/DaGame.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/Univers.hpp"
#include "cce/TileTemplate.hpp"
#include "cce/ImageManager.hpp"


using namespace cce;

int main()
{ 
    ImageManager::getInstance();
    cce::DaGame game;
    game.gameloop();
    
    return EXIT_SUCCESS;
}
