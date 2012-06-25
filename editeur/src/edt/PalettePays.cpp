#include "edt/PalettePays.hpp"
#include "cce/Palette.hpp"
#include "edt/GUI.hpp"
#include "edt/Carte.hpp"
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

void PalettePays::init(GUI const *gui, const string& conteneur, string nom, Carte* c)
{
    Palette::init(gui, conteneur, nom);
    carte = c;
    fenetre->setText("Palette de Pays");
    
    PushButton *tileButton = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/Spawn"));
    tileButton->setPosition(UVector2(UDim(0,0),UDim(0,0)));
    tileButton->setSize(UVector2(UDim(1.0f,0),UDim(0,32)));
    tileButton->setText("Placer le Point de Spawn");
    tileButton->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&PalettePays::setSpawn,this));
    fenetre->addChildWindow(tileButton);
}

bool PalettePays::setSpawn(const EventArgs &e)
{
    /*const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(e);
    PushButton* pb = static_cast<PushButton*>(wea.window);
    const char* nom = pb->getName().c_str();
    m->setTileTemplate(atoi(nom));*/
    return true;
}

}