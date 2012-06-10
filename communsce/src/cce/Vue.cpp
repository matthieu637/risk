#include "cce/Vue.hpp"
#include "cce/MoteurSFML.hpp"

using cce::Vue;

Vue::Vue()
{

}

void Vue::init(MoteurSFML* engine, GUI* gui)
{
    this->engine = engine;
    this->gui = gui;
}

void Vue::dessiner(const cce::Modele& m)
{
    engine->render<cce::Modele>(m);
}

