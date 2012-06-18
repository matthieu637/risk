#ifndef GUIEDITEUR_HPP
#define GUIEDITEUR_HPP
#include <cce/GUI.hpp>
#include <CEGUI/CEGUIScriptModule.h>

namespace edt{
  
class PaletteTile;
  
class GUI : public cce::GUI
{

public:
    GUI(const string& conteneur_);
    virtual ~GUI();
    void init(CEGUI::ScriptModule* module);

private:
    PaletteTile* palette_tile;
};

}

#endif // GUIEDITEUR_HPP
