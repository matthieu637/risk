#ifndef DAGAME_HPP
#define DAGAME_HPP


///
///\file DaGame.hpp
///\brief Application générale pour un jeu contenant le MVC
///\author matthieu
///

namespace cli{
class Modele;
class Vue;
class Controleur;
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
    Controleur* control;
    Modele* modele;
    Vue* vue;
};

}

#endif // DAGAME_HPP
