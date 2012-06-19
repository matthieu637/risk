#include "edt/GUI.hpp"
#include "edt/PaletteTile.hpp"
#include "edt/PaletteRegions.hpp"
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"
#include "cce/Console.hpp"

using namespace edt;

GUI::GUI(const string& conteneur_) : cce::GUI(conteneur_)
{

}

GUI::~GUI()
{

}

void GUI::init(CEGUI::ScriptModule* module)
{
    std::string conteneur = "Editeur";

    cce::GUI::init(module);
    palette_tile = new PaletteTile();
    palette_tile->init(this, conteneur, "Palette de tiles");
    palette_regions = new PaletteRegions();
    palette_regions->init(this, conteneur, "Palette de regions");
    console = new cce::Console(conteneur);

/*    initScrollPane(conteneur);*/
}

void GUI::initScrollPane(const std::string& conteneur)
{
    CEGUI::Scrollbar* sp = static_cast<CEGUI::Scrollbar*>(getRootWindow()->getChild("HSP"));
    //sp->set
    //sp->setContentPaneArea(CEGUI::Rect(0,0,1500,1500));
}

void GUI::updateListRegions(list<string> noms)
{
  palette_regions->updateListRegions(noms);
}
