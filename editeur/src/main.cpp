#include <iostream>
#include <cce/Tile.hpp>
#include <edt/Repere.hpp>
#include "cce/DaGame.hpp"
#include "bib/XMLEngine.hpp"

int main()
{
    new edt::Repere(5,8);
    
    cce::Carte c;
    bib::XMLEngine::save<cce::Carte>(c,"Carte", "map.bidon");
    
    cce::DaGame game;
    game.gameloop();
    
    return EXIT_SUCCESS;
}
