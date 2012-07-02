#include "edt/PalettePays.hpp"
#include "cce/Palette.hpp"
#include "edt/GUI.hpp"
#include "edt/Modele.hpp"
#include "edt/Controleur.hpp"
#include "cce/Univers.hpp"
#include "edt/Pays.hpp"
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
    
    //liste des pays
    liste_pays = static_cast<Listbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Listbox", "PaletteFrames/Pays/ListboxPays"));
    liste_pays->setSize(UVector2(UDim(1.0f,0),UDim(0.6f,0)));
    liste_pays->subscribeEvent(Listbox::EventSelectionChanged, Event::Subscriber(&PalettePays::onSelectionChange, this));
    fenetre->addChildWindow(liste_pays);
    
    //ajout des pays existants
    map<string, cce::Pays>* lr= m->getCarte()->getAllPays();
    map<string, cce::Pays>::iterator it;
    for(it = lr->begin(); it != lr->end(); it++)
      liste_pays->addItem(new ListboxTextItem(it->first));
    
    //editbox pour changer le nom du pays
    box_nom = static_cast<Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Pays/EditboxNom"));
    box_nom->setPosition(UVector2(UDim(0.02f,0),UDim(0.605f,0)));
    box_nom->setSize(UVector2(UDim(0.96f,0),UDim(0,32)));
    box_nom->subscribeEvent(Editbox::EventKeyUp, Event::Subscriber(&PalettePays::onNameChange, this));
    fenetre->addChildWindow(box_nom);
    
    //editbox pour changer l'income associé à la possession du pays
    box_income = static_cast<Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/Pays/EditboxIncome"));
    box_income->setPosition(UVector2(UDim(0.02f,0),UDim(0.610f,32)));
    box_income->setSize(UVector2(UDim(0.96f,0),UDim(0,32)));
    box_income->subscribeEvent(Editbox::EventKeyUp, Event::Subscriber(&PalettePays::onIncomeChange, this));
    fenetre->addChildWindow(box_income);
    
    //bouts pour définir le spawn
    PushButton *bouts = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/ButtonSpawn"));
    bouts->setPosition(UVector2(UDim(0.02f,0),UDim(0.615f,64)));
    bouts->setSize(UVector2(UDim(0.96f,0),UDim(0.04f,0)));
    bouts->setText("Definir spawn");
    bouts->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Controleur::onSetSpawn, c));
    fenetre->addChildWindow(bouts);
    
    //bouts pour afficher la liste des régions
    /*bouts = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/ButtonDeletePays"));
    bouts->setPosition(UVector2(UDim(0.02f,0),UDim(1.0f,-34)));
    bouts->setSize(UVector2(UDim(0.96f,0),UDim(0,32)));
    bouts->setText("Supprimer pays");
    bouts->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&PalettePays::onDeletePays, this));
    fenetre->addChildWindow(bouts);*/
    
    //bouts pour supprimer un pays de la liste
    bouts = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/ButtonDeletePays"));
    bouts->setPosition(UVector2(UDim(0.02f,0),UDim(0.910f,0)));
    bouts->setSize(UVector2(UDim(0.96f,0),UDim(0.04f,0)));
    bouts->setText("Supprimer pays");
    bouts->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&PalettePays::onDeletePays, this));
    fenetre->addChildWindow(bouts);
    
    //bouts pour ajouter un pays à la liste
    bouts = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button", "PaletteFrames/Pays/ButtonNewPays"));
    bouts->setPosition(UVector2(UDim(0.02f,0),UDim(0.955f,0)));
    bouts->setSize(UVector2(UDim(0.96f,0),UDim(0.04f,0)));
    bouts->setText("Nouveau pays");
    bouts->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&PalettePays::onNewPays, this));
    fenetre->addChildWindow(bouts);
}

bool PalettePays::onSelectionChange(const EventArgs &e)
{
    (void) e;
    if(liste_pays->getFirstSelectedItem() == nullptr)
      return true;
    
    ListboxTextItem* current_pays_item = (ListboxTextItem*) liste_pays->getFirstSelectedItem();
    
    //box nom
    box_nom->setText(current_pays_item->getText());
    
    //box income
    std::ostringstream oss;
    oss << modele->getCarte()->getPays(current_pays_item->getText().c_str())->getIncome();
    box_income->setText(oss.str());
    
    //modele current pays
    modele->setCurrentPays(current_pays_item->getText().c_str());
    
    //nom du pays séléctionné
    ancien = current_pays_item->getText().c_str();
    return true;
}

bool PalettePays::onNameChange(const EventArgs &e)
{
    (void) e;
    if(liste_pays->getFirstSelectedItem() == nullptr)
	return true;
    
    //Verif si le nom de pays dans la box est déjà dans la liste pour éviter un doublon
    for(unsigned int i=0; i<liste_pays->getItemCount(); i++)
      if(liste_pays->getListboxItemFromIndex(i)->getText() == box_nom->getText() && liste_pays->getListboxItemFromIndex(i) != liste_pays->getFirstSelectedItem())
	return true;
    
    const string &nouveau = box_nom->getText().c_str();
    
    if(nouveau.length() == 0 || nouveau == ancien){
	box_nom->setText(liste_pays->getFirstSelectedItem()->getText());
	return true;
    }
    
    Pays *p = (edt::Pays*) modele->getCarte()->getPays(ancien);
    modele->getCarte()->addPays(nouveau, *p);
    modele->getCarte()->getAllPays()->erase(ancien);
    liste_pays->getFirstSelectedItem()->setText(box_nom->getText());
    liste_pays->handleUpdatedItemData();
    ancien = liste_pays->getFirstSelectedItem()->getText().c_str();
    modele->setCurrentPays(liste_pays->getFirstSelectedItem()->getText().c_str());
    
    return true;
}

bool PalettePays::onIncomeChange(const EventArgs &e)
{
    (void) e;
    if(liste_pays->getFirstSelectedItem() == nullptr)
      return true;
    const string &nom = liste_pays->getFirstSelectedItem()->getText().c_str();
    Pays *p = (edt::Pays*) modele->getCarte()->getPays(nom);
    p->setIncome(atoi(box_income->getText().c_str()));
    return true;
}

bool PalettePays::onNewPays(const EventArgs &e)
{
    (void) e;
    const string &nom = "Nouveau Pays";
    for(unsigned int i=0; i<liste_pays->getItemCount(); i++)
      if(liste_pays->getListboxItemFromIndex(i)->getText() == nom)
	return true;
    const Pays p;
    modele->getCarte()->addPays(nom, p);
    ListboxTextItem* new_item = new ListboxTextItem(nom);
    liste_pays->addItem(new_item);
    
    return true;
}

bool PalettePays::onDeletePays(const EventArgs &e)
{
    (void) e;
    if(liste_pays->getFirstSelectedItem() == nullptr)
      return true;
    string nom = liste_pays->getFirstSelectedItem()->getText().c_str();
    if(modele->getCarte()->getPays(nom)->getPointSpawn() != nullptr)
      modele->getCarte()->getPays(nom)->getPointSpawn()->setColor(sf::Color(255,255,255,255));
    modele->getCarte()->getAllPays()->erase(nom);
    liste_pays->removeItem(liste_pays->getFirstSelectedItem());
    return true;
}

}