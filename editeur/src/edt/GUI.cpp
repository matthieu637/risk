#include "edt/GUI.hpp"
#include "edt/PaletteTile.hpp"
#include "edt/PaletteDecor.hpp"
#include "edt/PaletteRegions.hpp"
#include "edt/PalettePays.hpp"

#include <edt/Modele.hpp>
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"
#include "edt/Console.hpp"
#include "edt/Carte.hpp"
#include "edt/Modele.hpp"
#include "edt/Controleur.hpp"
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"

using namespace edt;

GUI::GUI(const string& conteneur) : cce::GUI(conteneur)
{

}

GUI::~GUI()
{

}

void GUI::init(Modele* modele, Controleur* controleur)
{
    cce::GUI::init(modele);
    this->controleur = controleur;
    this->modele = modele;
    
    console = new edt::Console(modele);
    loadCustomGUI();
}

void GUI::loadCustomGUI()
{
    palette_tile = new PaletteTile();
    palette_tile->init(this, "PaletteFrames/Tiles", (edt::Modele*)modele);
    palette_decor = new PaletteDecor();
    palette_decor->init(this, "PaletteFrames/Decors", (edt::Modele*)modele);
    palette_pays = new PalettePays();
    palette_pays->init(this, "PaletteFrames/Pays", (edt::Controleur*)controleur, (edt::Modele*)modele);
    palette_regions = new PaletteRegions();
    palette_regions->init(this, "PaletteFrames/Regions", modele);

    cce::Repere* rep = modele->getCarte()->getRepere();
    initScrollPane(rep->getHauteur(), rep->getLargeur());
}

void GUI::initScrollPane(int largeur, int hauteur)
{
    CEGUI::Scrollbar* vert = static_cast<CEGUI::Scrollbar*>(getRootWindow()->getChild("Editeur/VSB"));
    vert->setDocumentSize(hauteur*cce::Repere::h_tile_demi);
    vert->setPageSize(1);

    CEGUI::Scrollbar* hori = static_cast<CEGUI::Scrollbar*>(getRootWindow()->getChild("Editeur/HSB"));
    hori->setDocumentSize(largeur*cce::Repere::l_tile);
    hori->setPageSize(1);
}

void GUI::deleteGUI()
{
    delete palette_tile;
    delete palette_decor;
    delete palette_pays;
    delete palette_regions; 
}

void GUI::updateListRegions(list<string> noms)
{
    palette_regions->updateListRegions(noms);
}

