#ifndef GUIEDITEUR_HPP
#define GUIEDITEUR_HPP
#include <cce/GUI.hpp>
#include <CEGUI/CEGUIScriptModule.h>
#include <string.h>

using std::string;

namespace edt{
  
class PaletteTile;
class PaletteRegions;
  
class GUI : public cce::GUI
{

public:
    GUI(const string& conteneur_);
    virtual ~GUI();
    void init(CEGUI::ScriptModule* module);
    void updateListRegions(string noms);

private:
    PaletteTile* palette_tile;
    PaletteRegions* palette_regions;
};

}

#endif // GUIEDITEUR_HPP
