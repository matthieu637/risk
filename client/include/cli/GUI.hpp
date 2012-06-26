#ifndef GUICLIENT_HPP
#define GUICLIENT_HPP
#include <cce/GUI.hpp>
#include <CEGUI/CEGUIScriptModule.h>
#include <string>
#include <list>

using std::string;
using std::list;

namespace cce {
class Console;
}

namespace cli {
class Modele;
class PaletteTile;
class PaletteDecor;
class PaletteRegions;

class GUI : public cce::GUI
{

public:
    GUI(const string& conteneur_);
    virtual ~GUI();
    void init(Modele* module);
    cce::Console *getConsole();

private:

private:
    cce::Console* console;
};

}

#endif // GUIEDITEUR_HPP
