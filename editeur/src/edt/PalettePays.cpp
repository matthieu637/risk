#include "edt/PalettePays.hpp"
#include "cce/Palette.hpp"
#include "edt/GUI.hpp"
#include "edt/Modele.hpp"
#include "edt/Controleur.hpp"
#include "cce/Univers.hpp"
#include <CEGUI/elements/CEGUIPushButton.h>
#include <CEGUI/elements/CEGUIListbox.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
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
    
    liste_pays = static_cast<Listbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Listbox", "PaletteFrames/Pays/ListboxPays"));
    liste_pays->setWidth(UDim(1.0f,0));
    liste_pays->setHeight(UDim(0.75f,0));
    map<string, cce::Pays>* lr= m->getCarte()->getAllPays();
    map<string, cce::Pays>::iterator it;
    for(it = lr->begin(); it != lr->end(); it++)
      liste_pays->addItem(new ListboxTextItem(it->first));
    liste_pays->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&PalettePays::onSelectionChange, this));
    fenetre->addChildWindow(liste_pays);
    
    box_nom = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Pays/EditboxNom"));
    box_nom->setPosition(CEGUI::UVector2(UDim(0.02f,0),UDim(0.75f,2)));
    box_nom->setSize(UVector2(UDim(0.96f,0),UDim(0.0f,35)));
    box_nom->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&PalettePays::onNameChange, this));
    fenetre->addChildWindow(box_nom);
    
    box_income = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Pays/EditboxIncome"));
    box_income->setPosition(CEGUI::UVector2(UDim(0.02f,0),UDim(0.75f,37)));
    box_income->setSize(UVector2(UDim(0.96f,0),UDim(0.0f,35)));
    box_income->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&PalettePays::onIncomeChange, this));
    fenetre->addChildWindow(box_income);
    
    PushButton *bouts = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/ButtonSpawn"));
    bouts->setPosition(UVector2(UDim(0.02f,0),UDim(0.75f,74)));
    bouts->setSize(UVector2(UDim(0.96f,0),UDim(0,32)));
    bouts->setText("Definir spawn");
    bouts->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Controleur::onSetSpawn,c));
    fenetre->addChildWindow(bouts);
    
    bouts = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/ButtonNewPays"));
    bouts->setPosition(UVector2(UDim(0.02f,0),UDim(0.99f,-32)));
    bouts->setSize(UVector2(UDim(0.96f,0),UDim(0,32)));
    bouts->setText("Nouveau pays");
    bouts->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Controleur::onSetSpawn,c));
    fenetre->addChildWindow(bouts);
}

bool PalettePays::onSelectionChange(const EventArgs &e)
{
    const CEGUI::WindowEventArgs& wea = static_cast<const CEGUI::WindowEventArgs&>(e);
    current_pays_item = (ListboxTextItem*) liste_pays->getFirstSelectedItem();
    //box nom
    box_nom->setText(current_pays_item->getText());
    //box income
    std::ostringstream oss;
    oss << modele->getCarte()->getPays(current_pays_item->getText().c_str())->getIncome();
    box_income->setText(oss.str());
    
    return true;
}

bool PalettePays::onNameChange(const EventArgs &e)
{
    (void) e;
    if(current_pays_item != nullptr) {
        current_pays_item->setText(box_nom->getText());
        liste_pays->handleUpdatedItemData();
    }
    return true;	
}

bool PalettePays::onIncomeChange(const EventArgs &e)
{
    const CEGUI::KeyEventArgs& keyEvent = static_cast<const CEGUI::KeyEventArgs&>(e);
    
    return true;
}

}