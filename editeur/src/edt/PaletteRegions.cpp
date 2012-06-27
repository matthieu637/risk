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
    map<string, cce::Region* >* lr= m->getCarte()->getAllRegions();

    map<string, cce::Region* >::iterator it;
    for(it = lr->begin(); it != lr->end(); it++)
        lbox->addItem(new ListboxTextItem(it->first));

    lbox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&PaletteRegions::onChangeSelection,
                         this));

    ebox = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Regions/EditboxRegions"));
    fenetre->addChildWindow(ebox);
    ebox->setWidth(UDim(1,0));
    ebox->setHeight(UDim(0.0f,32));
    ebox->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.76,0)));

    ebox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&PaletteRegions::onNameChange, this));

    eboxinc = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Regions/EditboxIncomeRegions"));
    fenetre->addChildWindow(eboxinc);
    eboxinc->setWidth(UDim(1,0));
    eboxinc->setHeight(UDim(0.0f,32));
    eboxinc->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.76,34)));


    resetPoly = static_cast<CEGUI::PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Regions/ResetPoly"));
    fenetre->addChildWindow(resetPoly);
    resetPoly->setWidth(UDim(1,0));
    resetPoly->setHeight(UDim(0.0f,32));
    resetPoly->setText("Reset Polygone");
    resetPoly->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.76,64)));
    resetPoly->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PaletteRegions::onResetPoly, this));


    addPoint = static_cast<CEGUI::PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Regions/AddPoint"));
    fenetre->addChildWindow(addPoint);
    addPoint->setWidth(UDim(1,0));
    addPoint->setHeight(UDim(0.0f,32));
    addPoint->setText("Set Poly");
    addPoint->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.76,96)));
    addPoint->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PaletteRegions::onDefinirPoly, this));
}

void PaletteRegions::updateListRegions(list<string> noms)
{
    lbox->resetList();
    list<string>::iterator it;
    for (it = noms.begin(); it != noms.end(); it++)
        lbox->addItem(new ListboxTextItem(*it));
}


void PaletteRegions::hideAllPoly()
{
    map<string, cce::Region*> * allr = modele->getCarte()->getAllRegions();
    map<string, cce::Region* >::iterator it;
    for(it = allr->begin(); it != allr->end();  it++)
        it->second->setDraw(false);
    delete allr;
}

bool PaletteRegions::onChangeSelection(const CEGUI::EventArgs &e)
{
    (void)e;
    hideAllPoly();

    if(lbox->getFirstSelectedItem() != nullptr) {
        std::ostringstream oss;
        lbti=lbox->getFirstSelectedItem();
        cce::Region* r =modele->getCarte()->getRegion(lbti->getText().c_str());

        r->setDraw(true);
        ebox->setText(lbti->getText());
        oss << modele->getCarte()->getRegion(lbti->getText().c_str())->getIncome();
        eboxinc->setText(oss.str());
    } else {
        eboxinc->setText("");
        ebox->setText("");
    }

    return true;
}

bool PaletteRegions::onNameChange(const CEGUI::EventArgs &e)
{
    (void) e;
    if(lbti != nullptr) {
        lbti->setText(ebox->getText());
        lbox->handleUpdatedItemData();
    }
    return true;
}

bool PaletteRegions::onResetPoly(const CEGUI::EventArgs &e)
{
    (void) e;
    if(lbox->getFirstSelectedItem() != nullptr) {
        lbti=lbox->getFirstSelectedItem();
        cce::Region* r =modele->getCarte()->getRegion(lbti->getText().c_str());

        r->resetPoly();
    }
    return true;
}

bool PaletteRegions::onDefinirPoly(const CEGUI::EventArgs &e)
{
    (void) e;
    if(lbox->getFirstSelectedItem() != nullptr) {
        lbti=lbox->getFirstSelectedItem();
        cce::Region* r =modele->getCarte()->getRegion(lbti->getText().c_str());
	
	if(modele->getPoly() == nullptr)
	  modele->setPoly(new Polygon);
	else {
	    Polygon* p = modele->getPoly();
	    modele->unsetPoly();
	    p->setPointCount(p->getPointCount() - 1);
	    ((edt::Region*)r)->setZone(p);
	}
    }
    return true;
}


}
