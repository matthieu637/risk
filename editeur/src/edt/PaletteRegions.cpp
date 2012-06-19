#include "edt/PaletteRegions.hpp"
#include <CEGUI/elements/CEGUIListbox.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
#include <CEGUI/CEGUIUDim.h>
#include "edt/Region.hpp"
#include "edt/GUI.hpp"

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

void PaletteRegions::init(GUI const *gui, const string& conteneur, string nom)
{
    Palette::init(gui, conteneur, nom);
    
    lbox = static_cast<Listbox*>(WindowManager::getSingleton().createWindow("TaharezLook/Listbox", "ListboxRegions"));
    fenetre->addChildWindow(lbox);
    
    lbox->addItem(new ListboxTextItem("Barad-dur"));
    lbox->addItem(new ListboxTextItem("Isengard"));
    lbox->addItem(new ListboxTextItem("Edoras"));
    lbox->addItem(new ListboxTextItem("Minas Tirith"));
    lbox->addItem(new ListboxTextItem("Lothlorien"));
    lbox->setWidth(UDim(1.0f,0));
    lbox->setHeight(UDim(0.75f,0));
}

void PaletteRegions::updateListRegions(list<string> noms)
{
    lbox->resetList();
    list<string>::iterator it;
    for (it = noms.begin(); it != noms.end(); it++)
	lbox->addItem(new ListboxTextItem(*it));
}

}