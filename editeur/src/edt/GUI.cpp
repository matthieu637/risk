#include "edt/PaletteTile.hpp"
#include "edt/GUI.hpp"
#include <edt/PaletteRegions.hpp>
#include "CEGUI/CEGUIScriptModule.h"

using namespace edt;

GUI::GUI(const string& conteneur_) : cce::GUI(conteneur_)
{
    
}

GUI::~GUI()
{

}

void GUI::init(CEGUI::ScriptModule* module)
{
    cce::GUI::init(module);
    palette_tile = new PaletteTile();
    palette_tile->init(this, "Palette de tiles");
    palette_regions = new PaletteRegions();
    palette_regions->init(this, "Palette de regions");
}

void GUI::updateListRegions(list<string> noms)
{
  palette_regions->updateListRegions(noms);
}