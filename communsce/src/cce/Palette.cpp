#include "cce/Palette.hpp"
#include "cce/GUI.hpp"
#include <CEGUI/CEGUIWindowManager.h>

using CEGUI::WindowManager;
using CEGUI::FrameWindow;

namespace cce{

Palette::Palette()
{
}

Palette::~Palette()
{
    
}

void Palette::init(const GUI  *gui, const string& conteneur)
{
    fenetre = (FrameWindow*) WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow", "Palette de Tiles");
    fenetre->setVisible(true);
    
    //gui->getRootWindow()->getChild(conteneur)->addChildWindow(fenetre);
    gui->getRootWindow()->addChildWindow(fenetre);
}

}