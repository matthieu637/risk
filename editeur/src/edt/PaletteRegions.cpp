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
#include <edt/Pays.hpp>
#include "edt/Controleur.hpp"
#include "cce/Carte.hpp"

using CEGUI::WindowManager;
using CEGUI::Size;
using CEGUI::Listbox;
using CEGUI::ListboxTextItem;
using CEGUI::Editbox;
using CEGUI::UDim;
using CEGUI::Combobox;

namespace edt {

PaletteRegions::PaletteRegions()
{
    current_reg = nullptr;
}

PaletteRegions::~PaletteRegions()
{

}

void PaletteRegions::init(GUI const *gui, string nom, Modele* m,  Controleur* c)
{
    Palette::init(gui, nom);
    fenetre->subscribeEvent(CEGUI::Window::EventShown, CEGUI::Event::Subscriber(&PaletteRegions::onShow, this));
    
    control = c;
    modele=m;
    lbox = static_cast<Listbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Listbox", "PaletteFrames/Regions/ListboxRegions"));
    fenetre->addChildWindow(lbox);
    lbox->setWidth(UDim(1.0f,0));
    lbox->setHeight(UDim(0.35f,0));
    lbox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&PaletteRegions::onChangeSelection, this));

    ebox = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Regions/EditboxRegions"));
    fenetre->addChildWindow(ebox);
    ebox->setWidth(UDim(1,0));
    ebox->setHeight(UDim(0.0f,32));
    ebox->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.37,0)));
    ebox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&PaletteRegions::onRegionNameChange, this));


    eboxinc = static_cast<CEGUI::Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Regions/EditboxIncomeRegions"));
    fenetre->addChildWindow(eboxinc);
    eboxinc->setWidth(UDim(1,0));
    eboxinc->setHeight(UDim(0.0f,32));
    eboxinc->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.38,34)));
    eboxinc->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&PaletteRegions::onIncomeChange, this));


    resetPoly = static_cast<CEGUI::PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Regions/ResetPoly"));
    fenetre->addChildWindow(resetPoly);
    resetPoly->setWidth(UDim(1,0));
    resetPoly->setHeight(UDim(0.0f,32));
    resetPoly->setText("Reset Polygone");
    resetPoly->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.39,64)));
    resetPoly->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PaletteRegions::onResetPoly, this));


    addPoint = static_cast<CEGUI::PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Regions/AddPoint"));
    fenetre->addChildWindow(addPoint);
    addPoint->setWidth(UDim(1,0));
    addPoint->setHeight(UDim(0.0f,32));
    addPoint->setText("Set Poly");
    addPoint->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.40,96)));
    addPoint->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PaletteRegions::onDefinirPoly, this));

    cboxpoly = static_cast<CEGUI::Checkbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Checkbox", "PaletteFrames/Regions/CheckboxPoly"));
    fenetre->addChildWindow(cboxpoly);
    cboxpoly->setWidth(UDim(1,0));
    cboxpoly->setText("Montrer tous les polygones");
    cboxpoly->setHeight(UDim(0.0f,32));
    cboxpoly->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.41,128)));
    cboxpoly->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&PaletteRegions::onCheckedChange, this));

    comboBoxPays = static_cast<CEGUI::Combobox*>(WindowManager::getSingleton().createWindow("TaharezLook/Combobox", "PaletteFrames/Regions/ComboBoxPays"));
    fenetre->addChildWindow(comboBoxPays);
    comboBoxPays->setWidth(UDim(1,0));
    comboBoxPays->setHeight(UDim(0.0f,128));
    comboBoxPays->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.42,160)));
    comboBoxPays->setReadOnly(true);
    comboBoxPays->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&PaletteRegions::onComboboxSelectionChange, this));


    CEGUI::PushButton* newReg = static_cast<CEGUI::PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Regions/NewReg"));
    fenetre->addChildWindow(newReg);
    newReg->setWidth(UDim(1,0));
    newReg->setHeight(UDim(0.0f,32));
    newReg->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.42,196)));
    newReg->setText((CEGUI::utf8*)"Nouvelle Région");
    newReg->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PaletteRegions::onNewReg, this));


    CEGUI::PushButton* delReg = static_cast<CEGUI::PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Regions/RmReg"));
    fenetre->addChildWindow(delReg);
    delReg->setWidth(UDim(1,0));
    delReg->setHeight(UDim(0.0f,32));
    delReg->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.42,232)));
    delReg->setText((CEGUI::utf8*)"Supprimer Région");
    delReg->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PaletteRegions::onRmReg, this));
    
    CEGUI::PushButton* newFlag = static_cast<CEGUI::PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Regions/newFlag"));
    fenetre->addChildWindow(newFlag);
    newFlag->setWidth(UDim(1,0));
    newFlag->setHeight(UDim(0.0f,32));
    newFlag->setPosition(CEGUI::UVector2(UDim(0,0),UDim(0.42,270)));
    newFlag->setText((CEGUI::utf8*)"Ajouter Flag");
    newFlag->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&edt::Controleur::onSetFlag, c));
}


bool PaletteRegions::onNewReg(const CEGUI::EventArgs &e)
{
    (void) e;
    if(modele->getCarte()->getAllPays()->begin() == modele->getCarte()->getAllPays()->end())
        return true;

    Region r;
    r.setIncome(50);
    string pays = modele->getCarte()->getAllPays()->begin()->first;
    modele->getCarte()->getPays(pays)->addRegion("Nouvelle Région", r);
    lbox->addItem(new ListboxTextItem((CEGUI::utf8*)"Nouvelle Région"));

    return true;
}

bool PaletteRegions::onRmReg(const CEGUI::EventArgs &e)
{
    (void) e;
    if(lbox->getFirstSelectedItem() != nullptr)
    {
        string region = ebox->getText().c_str();
        string pays = modele->getCarte()->getPaysWithRegion(region);
        modele->getCarte()->getPays(pays)->getRegions()->erase(region);
        lbox->removeItem(lbox->getFirstSelectedItem());
        current_reg = nullptr;
    }
    return true;
}

bool PaletteRegions::onShow(const CEGUI::EventArgs &e)
{
    (void) e;
    reloadListBox();
    reloadPaysBox();
    return true;
}

void PaletteRegions::reloadListBox()
{
    lbox->resetList();

    map<string, cce::Region* >* lr= modele->getCarte()->getAllRegions();

    map<string, cce::Region* >::iterator it;
    for(it = lr->begin(); it != lr->end(); it++)
        lbox->addItem(new ListboxTextItem(it->first));

    delete lr;
}

void PaletteRegions::reloadPaysBox()
{
    comboBoxPays->resetList();

    map<string, cce::Pays>* mp= modele->getCarte()->getAllPays();
    map<string, cce::Pays>::iterator ite;

    for(ite = mp->begin(); ite != mp->end(); ite++)
    {
        ListboxTextItem* itemCombobox = new ListboxTextItem(ite->first);
        itemCombobox->setSelectionBrushImage("TaharezLook","MultiListSelectionBrush");
        comboBoxPays->addItem(itemCombobox);
    }
}

bool PaletteRegions::onComboboxSelectionChange(const CEGUI::EventArgs &e)
{
    (void) e;
    if(lbox->getFirstSelectedItem() != nullptr)
    {
        string region = ebox->getText().c_str();
        string ancienPays = modele->getCarte()->getPaysWithRegion(region);
        string nouveauPays = comboBoxPays->getText().c_str();

        if(ancienPays == nouveauPays)
            return true;
        modele->getCarte()->getPays(nouveauPays)->addRegion(region, *current_reg);
        modele->getCarte()->getPays(ancienPays)->getRegions()->erase(region);
        current_reg = (edt::Region*) modele->getCarte()->getRegion(region);
    }

    return true;
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

void PaletteRegions::showAllPoly()
{
    map<string, cce::Region*> * allr = modele->getCarte()->getAllRegions();
    map<string, cce::Region* >::iterator it;
    for(it = allr->begin(); it != allr->end();  it++)
        it->second->setDraw(true);
    delete allr;
}

bool PaletteRegions::onCheckedChange(const CEGUI::EventArgs &e)
{
    (void) e;
    if(cboxpoly->isSelected())
        showAllPoly();
    else
        hideAllPoly();

    return true;
}

bool PaletteRegions::onChangeSelection(const CEGUI::EventArgs &e)
{
    (void)e;
    CEGUI::ListboxItem* lbti=lbox->getFirstSelectedItem();

    if(!cboxpoly->isSelected())
        hideAllPoly();

     
    if(lbox->getFirstSelectedItem() != nullptr) {
        std::ostringstream oss;
        current_reg = (edt::Region*) modele->getCarte()->getRegion(lbti->getText().c_str());

        ebox->setText(lbti->getText());
	modele->setCurrentRegion(lbti->getText().c_str());
        current_reg->setDraw(true);
        oss << current_reg->getIncome();
        eboxinc->setText(oss.str());
        comboBoxPays->setText(modele->getCarte()->getPaysWithRegion(lbti->getText().c_str()));
    } else {
        eboxinc->setText("");
        ebox->setText("");
        comboBoxPays->setText("");
        current_reg = nullptr;
    }

    if(lbti != nullptr)
        ancien = lbti->getText().c_str();
    return true;
}

bool PaletteRegions::onRegionNameChange(const CEGUI::EventArgs &e)
{
    (void) e;
    if(current_reg == nullptr) {
        return true;
    }

    CEGUI::ListboxItem* lbti=lbox->getFirstSelectedItem();
    if(lbti != nullptr) {
        lbti->setText(ebox->getText());
        lbox->handleUpdatedItemData();
    }

    const string &nouveau = ebox->getText().c_str();
    if(nouveau.length() == 0 || nouveau == ancien) {
        ebox->setText(lbti->getText());
        return true;
    }

    //Region* r = new Region(*current_reg);
    map<string, cce::Pays>* mp= modele->getCarte()->getAllPays();
    map <string,cce::Pays>::iterator it;
    for (it = mp->begin(); it != mp->end(); it++)
        if(it->second.getRegion(ancien) != nullptr)
        {
            it->second.addRegion(nouveau, *current_reg);
            it->second.getRegions()->erase(ancien);
            current_reg = (edt::Region*) it->second.getRegion(nouveau);
            break;
        }

    ancien = nouveau;
    return true;
}

bool PaletteRegions::onIncomeChange(const CEGUI::EventArgs &e)
{
    (void) e;
    if(current_reg == nullptr) {
        return true;
    }
    current_reg->setIncome(atoi(eboxinc->getText().c_str()));

    return true;
}

bool PaletteRegions::onResetPoly(const CEGUI::EventArgs &e)
{
    (void) e;
    if(current_reg != nullptr)
        current_reg->resetPoly();

    return true;
}

bool PaletteRegions::onDefinirPoly(const CEGUI::EventArgs &e)
{
    (void) e;
    if(current_reg != nullptr) {
        if(modele->getPoly() == nullptr) {
            modele->setPoly(new sf::ConvexShape);
            addPoint->setText("Finish");
        } else {
            sf::ConvexShape* ch = modele->getPoly();
            modele->unsetPoly();

            Polygon* p = new Polygon(*ch);
            p->removeLastPoint();
            current_reg->setZone(p);
            addPoint->setText("Set Poly");
        }
    }
    return true;
}


}
