#ifndef VUE_HPP
#define VUE_HPP
#include "Modele.hpp"
#include "MoteurSFML.hpp"
#include "GUI.hpp"

namespace cce
{

class Vue
{

public:
    Vue();
    void init(MoteurSFML* engine, GUI* gui);
    void dessiner(const Modele& m);
private:
    MoteurSFML* engine;
    GUI* gui;
};

}
#endif // VUE_HPP
