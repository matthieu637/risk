#include "cce/Controleur.hpp"

namespace cce{

Controleur::Controleur()
{

}

void Controleur::init(MoteurSFML* engine, GUI* gui)
{
  this->engine = engine;
  this->gui = gui;
}

void Controleur::appliquer_events(const Modele& m){
    (void)m;
}

}
