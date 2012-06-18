#include <iostream>
#include "edt/DaGame.hpp"

#include "bib/XMLEngine.hpp"

int main()
{
    cce::Carte c;
    bib::XMLEngine::save<cce::Carte>(c, "Carte", "test.bidon");
  
  
    edt::DaGame game;
    game.gameloop();

    return EXIT_SUCCESS;
}
