#include "cce/Palette.hpp"
#include "cce/GUI.hpp"
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIVector.h>
#include <CEGUI/CEGUIUDim.h>

using CEGUI::WindowManager;
using CEGUI::FrameWindow;
using CEGUI::UVector2;
using CEGUI::UDim;

namespace cce{

Palette::Palette()
{
}

Palette::~Palette()
{
    
}

void Palette::init(GUI const *gui, const string& conteneur, string nom)
{
    fenetre = (FrameWindow*) WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow", nom);
    fenetre->setSize(UVector2(UDim(0.0f,200), UDim(0.0f,600)));
    fenetre->setVisible(true);
    
    //gui->getRootWindow()->getChild(conteneur)->addChildWindow(fenetre);

    gui->getRootWindow()->addChildWindow(fenetre);
}

}