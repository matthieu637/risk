#include "edt/PaletteRegions.hpp"
#include <CEGUI/elements/CEGUIListbox.h>
#include <CEGUI/elements/CEGUIEditbox.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
#include <CEGUI/CEGUIUDim.h>
#include <CEGUI/CEGUIVector.h>
#include "edt/Region.hpp"
#include "edt/GUI.hpp"
#include <edt/Carte.hpp>
#include <edt/Modele.hpp>
#include "cce/Carte.hpp"

using CEGUI::WindowManager;
using CEGUI::Size;
using CEGUI::Listbox;
using CEGUI::ListboxTextItem;
using CEGUI::Editbox;
using CEGUI::UDim;

namespace edt {

PaletteRegions::PaletteRegions()
{
  lbti=nullptr;
}

PaletteRegions::~PaletteRegions()
{

}

void PaletteRegions::init(GUI const *gui, string nom, Modele* m)
{
    Palette::init(gui, nom);

    modele=m;
    lbox = static_cast<Listbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Listbox", "PaletteFrames/Regions/ListboxRegions"));
    fenetre->addChildWindow(lbox);
    lbox->setWidth(UDim(1.0f,0));
    lbox->setHeight(UDim(0.75f,0));
    map<string, cce::Region>* lr= m->getCarte()->getAllRegions();

    map<string, cce::Region>::iterator it;
    for(it = lr->begin(); it != lr->end(); it++)
        lbox->addItem(new ListboxTextItem(it->first));

    lbox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&PaletteRegions::onChangeSelection,
                         this));

    ebox = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Regions/EditboxRegions"));
    fenetre->addChildWindow(ebox);
    ebox->setWidth(UDim(1,0));
    ebox->setHeight(UDim(0.0f,25));
    ebox->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.76,0)));

    ebox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&PaletteRegions::onNameChange, this));

    eboxinc = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Regions/EditboxIncomeRegions"));
    fenetre->addChildWindow(eboxinc);
    eboxinc->setWidth(UDim(1,0));
    eboxinc->setHeight(UDim(0.0f,25));
    eboxinc->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.76,28)));

}

void PaletteRegions::updateListRegions(list<string> noms)
{
    lbox->resetList();
    list<string>::iterator it;
    for (it = noms.begin(); it != noms.end(); it++)
        lbox->addItem(new ListboxTextItem(*it));
}


bool PaletteRegions::onChangeSelection(const CEGUI::EventArgs &e)
{
    std::ostringstream oss;
    const CEGUI::WindowEventArgs& wea = static_cast<const CEGUI::WindowEventArgs&>(e);
    lbti=lbox->getFirstSelectedItem();
    ebox->setText(lbti->getText());
    oss << modele->getCarte()->getRegion(lbti->getText().c_str())->getIncome();
    LOG_DEBUG(modele->getCarte()->getRegion(lbti->getText().c_str())->getIncome());
    eboxinc->setText(oss.str());
    return true;
}

bool PaletteRegions::onNameChange(const CEGUI::EventArgs &e)
{
    const CEGUI::KeyEventArgs& keyEvent = static_cast<const CEGUI::KeyEventArgs&>(e);
    if(lbti != nullptr) {
        lbti->setText(ebox->getText());
        lbox->handleUpdatedItemData();
    }
    return true;
}


}
