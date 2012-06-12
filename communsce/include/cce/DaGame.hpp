#ifndef DAGAME_HPP
#define DAGAME_HPP
#include "Controleur.hpp"
#include "Vue.hpp"
#include "Modele.hpp"
#include "cce/MoteurSFML.hpp"

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
    MoteurSFML* ms;
    Controleur* control;
    Modele* modele;
    Vue* vue;
};

}

#endif // DAGAME_HPP
