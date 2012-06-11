#include <iostream>
#include <cce/Tile.hpp>
#include <edt/Repere.hpp>
#include "cce/DaGame.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/Univers.hpp"

int main()
{
    new edt::Repere(5,8);
    
    cce::Univers u;
    bib::XMLEngine::save<cce::Univers>(u, "Univers","data/sf.univ");
    
    cce::DaGame game;
    game.gameloop();
    
    return EXIT_SUCCESS;
}
