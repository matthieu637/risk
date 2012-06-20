#include "edt/Vue.hpp"
#include "edt/GUI.hpp"

#include "bib/Logger.hpp"
#include <cce/MoteurSFML.hpp>
#include <CEGUI/elements/CEGUIScrollbar.h>

namespace edt {

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

void Vue::updateScrollVert(float newpos)
{
  //CEGUI::Scrollbar* sb = static_cast<CEGUI::Scrollbar*>(getGUI()->getRootWindow()->getChild("Editeur/VSB"));
  //sb->set
  //gui->
  sf::View* v = engine->getView();
  LOG_DEBUG(newpos);
  v->setCenter(v->getCenter().x, newpos);
}

void Vue::updateScrollHori(float newpos)
{
  sf::View* v = engine->getView();
  v->setCenter(newpos, v->getCenter().y);
}

}
