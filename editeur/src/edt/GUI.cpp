#include "edt/PaletteTile.hpp"
#include "edt/GUI.hpp"
#include "CEGUI/CEGUIScriptModule.h"
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
    cce::GUI::init(module);
    palette_tile = new PaletteTile();
    palette_tile->init(this, "Editeur/Pane");
    console = new cce::Console("Editeur/Pane");
}