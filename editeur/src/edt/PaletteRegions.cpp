#include "edt/PaletteRegions.hpp"
#include "edt/Palette.hpp"
#include <CEGUI/elements/CEGUIListbox.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
#include <CEGUI/CEGUIUDim.h>
#include "edt/Region.hpp"

using CEGUI::WindowManager;
using CEGUI::Size;
using CEGUI::Listbox;
using CEGUI::ListboxTextItem;

namespace edt{
  PaletteRegions::PaletteRegions()
  {
  }
  
  PaletteRegions::~PaletteRegions()
  {
    
  }
  
  void PaletteRegions::init(GUI const *gui, string nom)
  {
    Palette::init(gui, nom);
    
    //Add a listbox:	    
    
    lbox = static_cast<Listbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Listbox", "Root/Listbox1"));
    fenetre->addChildWindow(lbox);
    
     //Add the top 5 of the GPWiki forums:
    lbox->addItem(new ListboxTextItem("Ryan"));
    lbox->addItem(new ListboxTextItem("Ryan"));
    lbox->addItem(new ListboxTextItem("Ryan"));
    lbox->addItem(new ListboxTextItem("Machaira"));
    lbox->addItem(new ListboxTextItem("Codehead"));
    lbox->setHeight(CEGUI::UDim(1,100));
    lbox->setWidth(CEGUI::UDim(1,100));

  }
  
  void PaletteRegions::updateListRegions(string noms)
  {
    lbox->resetList();
    
	list <Region>::iterator it;
	lr.end();
	for (it = lr.begin(); it != lr.end(); it++)
	    lbox->addItem(new ListboxTextItem((*it).getNom()));
  }
  
  

}