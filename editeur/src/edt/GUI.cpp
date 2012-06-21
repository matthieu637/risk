#include "edt/GUI.hpp"
#include "edt/PaletteTile.hpp"
#include "edt/PaletteDecor.hpp"
#include "edt/PaletteRegions.hpp"

#include <edt/Modele.hpp>
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"
#include "edt/Console.hpp"

#include "cce/Carte.hpp"
#include "edt/Carte.hpp"
#include "cce/Modele.hpp"
#include "edt/Modele.hpp"
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"

using namespace edt;

GUI::GUI(const string& conteneur_) : cce::GUI(conteneur_)
{
  
}

GUI::~GUI()
{

}

void GUI::init(Modele* modele)
{
    std::string conteneur = "Editeur";

    cce::GUI::init(modele);
    palette_tile = new PaletteTile();
    palette_tile->init(this, conteneur, "PaletteFrames/Tiles", (edt::Modele*)modele);
    palette_decor = new PaletteDecor();
    palette_decor->init(this, conteneur, "PaletteFrames/Decors", (edt::Modele*)modele);
    
    edt::Carte* c=static_cast <edt::Carte*>(modele->getCarte());
    console = new edt::Console(conteneur,modele);
    
    palette_regions = new PaletteRegions();
    palette_regions->init(this, conteneur, "PaletteFrames/Regions", c);
/*    initScrollPane(conteneur);*/
}


cce::Console *GUI::getConsole(){
  return console;
}

void GUI::initScrollPane(const std::string& conteneur, Modele* modele)
{
  (void) modele;
  (void) conteneur;
    //CEGUI::Scrollbar* sp = static_cast<CEGUI::Scrollbar*>(getRootWindow()->getChild("HSP"));
    //sp->set
    //sp->set
    
    //sp->setPageSize(1000);
    //sp->setDocumentSize(10000);
    //sp
    //sp->setContentPaneArea(CEGUI::Rect(0,0,1500,1500));
}

void GUI::updateListRegions(list<string> noms)
{
  palette_regions->updateListRegions(noms);
}
