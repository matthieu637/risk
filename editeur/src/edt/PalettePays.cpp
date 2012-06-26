#include "edt/PalettePays.hpp"
#include "cce/Palette.hpp"
#include "edt/GUI.hpp"
#include "edt/Modele.hpp"
#include "edt/Controleur.hpp"
#include "cce/Univers.hpp"
#include <CEGUI/elements/CEGUIPushButton.h>
#include <CEGUI/CEGUIEvent.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <CEGUI/CEGUISubscriberSlot.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIFont.h>

using namespace CEGUI;

namespace edt{

PalettePays::PalettePays()
{

}

PalettePays::~PalettePays()
{

}

void PalettePays::init(GUI const *gui, const string& conteneur, string nom, Controleur* c)
{
    Palette::init(gui, conteneur, nom);
    control = c;
    fenetre->setText("Palette de Pays");
    
    PushButton *tileButton = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/Spawn"));
    tileButton->setPosition(UVector2(UDim(0.01f,0),UDim(0.01f,0)));
    tileButton->setSize(UVector2(UDim(0.98f,0),UDim(0,32)));
    tileButton->setText("Placer spawn");
    tileButton->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Controleur::onSetSpawn,c));
    fenetre->addChildWindow(tileButton);
}

}