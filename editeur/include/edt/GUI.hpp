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
class Modele;
class PaletteTile;
class PaletteRegions;
  
class GUI : public cce::GUI
{

public:
    GUI(const string& conteneur_);
    virtual ~GUI();
    void init(const Modele* module);
    void updateListRegions(list<string> noms);

private:
    void initScrollPane(const string& conteneur);

private:
    PaletteTile* palette_tile;
    PaletteRegions* palette_regions;
    cce::Console* console;
};

}

#endif // GUIEDITEUR_HPP
