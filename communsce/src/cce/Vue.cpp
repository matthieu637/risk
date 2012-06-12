#include "cce/Vue.hpp"
#include "cce/Modele.hpp"
#include "cce/MoteurSFML.hpp"

using cce::Vue;

namespace cce{

Vue::Vue()
{

}

void Vue::init(MoteurSFML* engine, GUI* gui, Modele* m)
{
    this->engine = engine;
    this->gui = gui;
    this->modele = m;
}

void Vue::dessiner(cce::Modele* m)
{
    engine->render<cce::Modele>(*m);
}

void Vue::updateCamera(int x, int y)
{
    engine->getView()->setCenter(x, y);
}

}