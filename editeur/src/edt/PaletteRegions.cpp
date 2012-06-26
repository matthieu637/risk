#include "edt/PaletteRegions.hpp"
#include <CEGUI/elements/CEGUIListbox.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
#include <CEGUI/CEGUIUDim.h>
#include "edt/Region.hpp"
#include "edt/GUI.hpp"
#include <edt/Carte.hpp>
#include "cce/Carte.hpp"

using CEGUI::WindowManager;
using CEGUI::Size;
using CEGUI::Listbox;
using CEGUI::ListboxTextItem;
using CEGUI::UDim;

namespace edt{
  
PaletteRegions::PaletteRegions()
{
}

PaletteRegions::~PaletteRegions()
{
  
}

void PaletteRegions::init(GUI const *gui, string nom, Carte* c)
{
    Palette::init(gui, nom);
    
    lbox = static_cast<Listbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Listbox", "ListboxRegions"));
    fenetre->addChildWindow(lbox);
     lbox->setWidth(UDim(1.0f,0));
      lbox->setHeight(UDim(0.75f,0));
    map<string, cce::Region>* lr= c->getAllRegions();
    
    map<string, cce::Region>::iterator it;
    for(it = lr->begin(); it != lr->end(); it++)
    {
      lbox->addItem(new ListboxTextItem(it->first));
     
    }
}

void PaletteRegions::updateListRegions(list<string> noms)
{
    lbox->resetList();
    list<string>::iterator it;
    for (it = noms.begin(); it != noms.end(); it++)
	lbox->addItem(new ListboxTextItem(*it));
}

}