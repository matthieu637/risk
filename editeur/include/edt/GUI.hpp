#ifndef GUIEDITEUR_HPP
#define GUIEDITEUR_HPP
#include <cce/GUI.hpp>
#include <CEGUI/CEGUIScriptModule.h>

namespace cce {
class Console;
}

namespace edt {

class PaletteTile;

class GUI : public cce::GUI
{

public:
    GUI(const string& conteneur_);
    virtual ~GUI();
    void init(CEGUI::ScriptModule* module);

private:
    void initScrollPane(const std::string& conteneur);

private:
    PaletteTile* palette_tile;
    cce::Console* console;
};

}

#endif // GUIEDITEUR_HPP
