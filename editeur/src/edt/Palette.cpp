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

void Palette::init(GUI const *gui, string nom)
{
    fenetre = (FrameWindow*) WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow", nom);
    fenetre->setVisible(true);
    
    gui->getRootWindow()->addChildWindow(fenetre);
}

}