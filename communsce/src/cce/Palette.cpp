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

void Palette::init(GUI const *gui, string nom)
{
    fenetre = (FrameWindow*) WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow", nom);
    fenetre->setSize(UVector2(UDim(0.25f, 0), UDim(0.45f,0)));
    fenetre->setPosition(UVector2(UDim(0.79f, -15), UDim(0.03f,0)));
    fenetre->setCloseButtonEnabled(true);
    fenetre->subscribeEvent(FrameWindow::EventCloseClicked,CEGUI::Event::Subscriber(&Palette::onClose, this));
    fenetre->setVisible(false);
    fenetre->setSizingEnabled(false);
    
    //gui->getRootWindow()->getChild(conteneur)->addChildWindow(fenetre);
    gui->getRootWindow()->addChildWindow(fenetre);
}

bool Palette::onClose(const CEGUI::EventArgs&)
{
    fenetre->setVisible(false);
    return true;
}

}