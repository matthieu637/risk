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

void PalettePays::init(GUI const *gui, string nom, Controleur* c, Modele* m)
{
    Palette::init(gui, nom);
    control = c;
    modele = m;
    fenetre->setText("Palette de Pays");
    Palette::init(gui, nom);
    
    liste_pays = static_cast<Listbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Listbox", "PaletteFrames/Regions/ListboxPays"));
    liste_pays->setWidth(UDim(1.0f,0));
    liste_pays->setHeight(UDim(0.75f,0));
    map<string, cce::Pays>* lr= m->getCarte()->getAllPays();
    
    map<string, cce::Pays>::iterator it;
    for(it = lr->begin(); it != lr->end(); it++)
      liste_pays->addItem(new ListboxTextItem(it->first));
    
    liste_pays->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&PalettePays::onChangeSelection, this));
    fenetre->addChildWindow(liste_pays);
    
    box_nom = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Regions/EditboxRegions"));
    fenetre->addChildWindow(box_nom);
    box_nom->setWidth(UDim(1,0));
    box_nom->setHeight(UDim(0.0f,25));
    box_nom->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.76,0)));
    
    box_nom->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&PalettePays::onNameChange, this));
    
    PushButton *tileButton = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/Spawn"));
    tileButton->setPosition(UVector2(UDim(0.01f,0),UDim(0.01f,0)));
    tileButton->setSize(UVector2(UDim(0.98f,0),UDim(0,32)));
    tileButton->setText("Définir spawn");
    tileButton->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Controleur::onSetSpawn,c));
    fenetre->addChildWindow(tileButton);
    
    tileButton = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/NewPays"));
    tileButton->setPosition(UVector2(UDim(0.01f,0),UDim(0.01f,0)));
    tileButton->setSize(UVector2(UDim(0.98f,0),UDim(0,32)));
    tileButton->setText("Nouveau pays");
    tileButton->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Controleur::onSetSpawn,c));
    fenetre->addChildWindow(tileButton);
}

bool PalettePays::onChangeSelection(const CEGUI::EventArgs &e)
{
    std::ostringstream oss;
    const CEGUI::WindowEventArgs& wea = static_cast<const CEGUI::WindowEventArgs&>(e);
    ListboxTextItem pays = liste_pays->getFirstSelectedItem();
    ebox->setText(pays->getText());
    oss << modele->getCarte()->getRegion(pays->getText().c_str())->getIncome();
    LOG_DEBUG(modele->getCarte()->getRegion(pays->getText().c_str())->getIncome());
    eboxinc->setText(oss.str());
    return true;
}

}