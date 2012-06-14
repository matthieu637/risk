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
    m->addVue(this);
}

void Vue::dessiner(cce::Modele* m)
{
    engine->render<cce::Modele>(*m);
}

void Vue::updateCameraPosition(int x, int y)
{
    engine->getView()->setCenter(x, y);
}

void Vue::updateCameraZoom(float factor)
{
    engine->getView()->zoom(factor);
}

void Vue::resetCameraZoom()
{
    engine->getView()->setSize(engine->getFenetre()->getSize().x, engine->getFenetre()->getSize().y);
}

}