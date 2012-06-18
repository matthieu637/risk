#include "edt/Palette.hpp"
#include "edt/GUI.hpp"
#include <CEGUI/CEGUIWindowManager.h>

using CEGUI::WindowManager;
using CEGUI::FrameWindow;

namespace edt{

Palette::Palette()
{
}

Palette::~Palette()
{
    
}

void Palette::init(GUI const *gui)
{
    fenetre = (FrameWindow*) WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow", "Palette de Tiles");
    fenetre->setVisible(true);
    
    gui->getRootWindow()->addChildWindow(fenetre);
}

}