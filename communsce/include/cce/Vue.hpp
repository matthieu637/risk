#ifndef VUE_HPP
#define VUE_HPP

///
///\file Vue.hpp
///\brief Gere l'affichage de SFML et de CEGUI
///\author matthieu
///

namespace cce
{
class MoteurSFML;
class GUI;
class Modele;

class Vue
{

public:
    Vue();
///
///\brief Simple setter, engine et gui doivent être les mêmes que celui du controleur
///
    void init(MoteurSFML* engine, GUI* gui, Modele* m);
///
///\brief Rend le modèle et la gui
///
    void dessiner(Modele* m);
///
///\brief Repositionne la cam selon le modele
///
    void updateCameraPosition(int x, int y);
///
///\brief Zoom par un facteur
///
    void updateCameraZoom(float factor);
///
///\brief Remet le zoom à 0
///
    void resetCameraZoom();
    
private:
    MoteurSFML* engine;
    GUI* gui;
    Modele* modele;
};

}
#endif // VUE_HPP
