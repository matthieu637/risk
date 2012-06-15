#include <iostream>
#include "cce/Tile.hpp"
#include "edt/Repere.hpp"
#include "edt/DaGame.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/Univers.hpp"
#include "cce/TileTemplate.hpp"
#include "cce/ImageManager.hpp"


using namespace cce;

int main()
{ 
    ImageManager::getInstance();
    edt::DaGame game;
    game.gameloop();
    
    return EXIT_SUCCESS;
}
