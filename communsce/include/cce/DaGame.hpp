#ifndef DAGAME_HPP
#define DAGAME_HPP
#include "Controleur.hpp"
#include "Vue.hpp"

namespace cce{

class DaGame
{

public:
    DaGame();
    void gameloop();
private:
    Controleur control;
    Modele modele;
    Vue vue;
};

}

#endif // DAGAME_HPP
