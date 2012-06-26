#ifndef GUIEDITEUR_HPP
#define GUIEDITEUR_HPP
#include <cce/GUI.hpp>
#include <CEGUI/CEGUIScriptModule.h>
#include <string>
#include <list>

using std::string;
using std::list;

namespace cce {
class Console;
}

namespace edt {
class Controleur;
class Modele;
class PaletteTile;
class PaletteDecor;
class PaletteRegions;
class PalettePays;
  
class GUI : public cce::GUI
{

public:
    GUI(const string& conteneur);
    virtual ~GUI();
    void init(Modele* module, Controleur* controleur);
    void initScrollPane(int largeur, int hauteur);
    void updateListRegions(list<string> noms);
    cce::Console *getConsole();
    
private:
    

private:
    PaletteTile* palette_tile;
    PaletteDecor* palette_decor;
    PaletteRegions* palette_regions;
    PalettePays* palette_pays;
    cce::Console* console;
};

}

#endif // GUIEDITEUR_HPP
