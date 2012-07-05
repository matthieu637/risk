#include "edt/PaletteInformationSelection.hpp"
#include "cce/Palette.hpp"
#include "edt/GUI.hpp"
#include "edt/Modele.hpp"
#include "edt/Controleur.hpp"
#include "cce/Univers.hpp"
#include "cce/Decor.hpp"
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

PaletteInformationSelection::PaletteInformationSelection()
{

}

PaletteInformationSelection::~PaletteInformationSelection()
{

}

void PaletteInformationSelection::init(GUI const *gui, string nom, Controleur* c, Modele* m)
{
    Palette::init(gui, nom);
    control = c;
    modele = m;
    fenetre->setText("Informations sur selection");
      
    CEGUI::MenuItem* taille_socle_nom = static_cast<MenuItem*>(WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "PaletteFrames/InformationsSelection/MenuItemSocleNom"));
    taille_socle_nom->setText("Taille Socle");
    taille_socle_nom->setPosition(UVector2(UDim(0.02f,0),UDim(0.605f,0)));
    taille_socle_nom->setSize(UVector2(UDim(0.96f,0),UDim(0,32)));
    fenetre->addChildWindow(taille_socle_nom);
    
    socle_taille = static_cast<Editbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Editbox", "PaletteFrames/InformationsSelection/EditboxSocleTaille"));
    socle_taille->setPosition(UVector2(UDim(0.02f,0),UDim(0.605f,32)));
    socle_taille->setSize(UVector2(UDim(0.96f,0),UDim(0,32)));
    socle_taille->subscribeEvent(Editbox::EventKeyUp, Event::Subscriber(&PaletteInformationSelection::onTailleSocleChange, this));
    fenetre->addChildWindow(socle_taille);
    
}

bool PaletteInformationSelection::onTailleSocleChange(const CEGUI::EventArgs &e){
  (void)e;
  
  current_selection->getSelectionCircle()->setRadius(atoi(socle_taille->getText().c_str()));

  return true;
}

void PaletteInformationSelection::setCurrentSelection(cce::Decor* d)
{
  current_selection = d;
  this->update();
}

void PaletteInformationSelection::update(){
  if(current_selection != nullptr){
    
    //Mise à jour du rayon du socle
    std::ostringstream ss;
    ss << current_selection->getSelectionCircle()->getRadius();
    socle_taille->setText(ss.str());
    
  }
}

}