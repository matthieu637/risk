#include "edt/Vue.hpp"
#include "edt/GUI.hpp"

#include "bib/Logger.hpp"

namespace edt{

Vue::Vue(cce::MoteurSFML* engine, GUI* gui) : cce::Vue(engine, gui)
{

}

Vue::~Vue()
{

}

void Vue::updateCameraPosition(int x, int y)
{
    cce::Vue::updateCameraPosition(x,y);
}
    
GUI* Vue::getGUI()
{
  return (GUI*)gui;
}

void Vue::updateListRegions(list<string> noms)
{
   getGUI()->updateListRegions(noms);
}

}