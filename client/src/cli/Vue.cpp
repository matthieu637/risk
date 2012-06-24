#include "cli/Vue.hpp"
#include "cli/GUI.hpp"

#include "bib/Logger.hpp"
#include <cce/MoteurSFML.hpp>
#include <CEGUI/elements/CEGUIScrollbar.h>
#include <CEGUI/elements/CEGUIThumb.h>

namespace cli {

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

void Vue::updateCameraZoom(float factor)
{
    cce::Vue::updateCameraZoom(factor);
}

void Vue::updateSize(int width, int height)
{
    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Size(width, height));
}

}
