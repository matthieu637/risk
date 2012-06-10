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
    void init(MoteurSFML* engine, GUI* gui);
///
///\brief Rend le modèle et la gui
///
    void dessiner(const Modele& m);
private:
    MoteurSFML* engine;
    GUI* gui;
};

}
#endif // VUE_HPP
