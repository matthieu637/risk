#include "edt/GUI.hpp"
#include "edt/PaletteTile.hpp"
#include "edt/PaletteDecor.hpp"
#include "edt/PaletteRegions.hpp"
#include "edt/PalettePays.hpp"

#include <edt/Modele.hpp>
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"
#include "edt/Console.hpp"

#include "cce/Carte.hpp"
#include "edt/Carte.hpp"
#include "cce/Modele.hpp"
#include "edt/Modele.hpp"
#include "edt/Controleur.hpp"
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"

using namespace edt;

GUI::GUI(const string& conteneur_) : cce::GUI(conteneur_)
{
  
}

GUI::~GUI()
{

}

void GUI::init(Modele* modele, Controleur* controleur)
{
    std::string conteneur = "Editeur";

    cce::GUI::init(modele);
    
    edt::Carte* c=static_cast <edt::Carte*>(modele->getCarte());
    
    palette_tile = new PaletteTile();
    palette_tile->init(this, conteneur, "PaletteFrames/Tiles", (edt::Modele*)modele);
    palette_decor = new PaletteDecor();
    palette_decor->init(this, conteneur, "PaletteFrames/Decors", (edt::Modele*)modele);
    palette_pays = new PalettePays();
    palette_pays->init(this, conteneur, "PaletteFrames/Pays", (edt::Controleur*)controleur);
    palette_regions = new PaletteRegions();
    palette_regions->init(this, conteneur, "PaletteFrames/Regions", c);
    
    console = new edt::Console(conteneur,modele);
    
    cce::Repere* rep = modele->getCarte()->getRepere();
    initScrollPane(conteneur, rep->getHauteur(), rep->getLargeur());
}


cce::Console *GUI::getConsole(){
  return console;
}

void GUI::initScrollPane(const std::string& conteneur, int largeur, int hauteur)
{
  (void) conteneur;
  
  CEGUI::Scrollbar* vert = static_cast<CEGUI::Scrollbar*>(getRootWindow()->getChild("Editeur/VSB"));
  vert->setDocumentSize(hauteur*cce::Repere::h_tile_demi);
  vert->setPageSize(1);
    
  CEGUI::Scrollbar* hori = static_cast<CEGUI::Scrollbar*>(getRootWindow()->getChild("Editeur/HSB"));
  hori->setDocumentSize(largeur*cce::Repere::l_tile);
  hori->setPageSize(1);
}

void GUI::updateListRegions(list<string> noms)
{
  palette_regions->updateListRegions(noms);
}
