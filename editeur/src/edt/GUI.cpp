#include "edt/GUI.hpp"
#include "edt/PaletteTile.hpp"
#include "edt/PaletteRegions.hpp"
#include <edt/Modele.hpp>
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"
#include "cce/Console.hpp"
#include "cce/Carte.hpp"
#include "edt/Carte.hpp"
#include "cce/Modele.hpp"

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
    palette_tile->init(this, conteneur, "Palette de tiles");
    palette_regions = new PaletteRegions();
    
    
    edt::Carte* c=static_cast <edt::Carte*>(modele->getCarte());
     palette_regions->init(this, conteneur, "Palette de regions", c);
    console = new cce::Console(conteneur);
/*    initScrollPane(conteneur);*/
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
