#include "edt/Vue.hpp"
#include "edt/GUI.hpp"

namespace edt{

Vue::Vue(cce::MoteurSFML* engine, GUI* gui) : cce::Vue(engine, gui)
{

}

Vue::~Vue()
{

}

GUI* Vue::getGUI()
{
  return (GUI*)gui;
}

void Vue::updateListRegions(string noms)
{
   getGUI()->updateListRegions(noms);
}

}