#ifndef DAGAME_HPP
#define DAGAME_HPP
#include "Controleur.hpp"
#include "Vue.hpp"

///
///\file DaGame.hpp
///\brief Application générale pour un jeu contenant le MVC
///\author matthieu
///

namespace cce{

class DaGame
{

public:
    DaGame();
///
///\brief Boucle principale de traitement des évènements, mise à jour du modèle 
///       et d'affichage du rendu
///
    void gameloop();
private:
    Controleur control;
    Modele modele;
    Vue vue;
};

}

#endif // DAGAME_HPP
