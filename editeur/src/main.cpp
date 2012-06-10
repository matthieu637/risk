#include <iostream>
#include <cce/Tile.hpp>
#include <edt/Repere.hpp>
#include "cce/DaGame.hpp"

int main()
{
    edt::Repere *r = new edt::Repere(5,8);
    
    cce::DaGame game;
    game.gameloop();
    
    return EXIT_SUCCESS;
}
