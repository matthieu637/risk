#include "cli/Console.hpp"
#include "bib/Logger.hpp"
#include "cce/Controleur.hpp" //BIND
#include <cce/Modele.hpp>


namespace cli {
Console::Console(Modele *modele) : cce::Console()
{
    mapCommandes["open"] = BIND(&Console::onOpen);
    mapCommandes["quit"] = BIND(&Console::onQuit);
    m = modele;
}

CEGUI::String Console::onOpen(const CEGUI::String& s) {
    LOG_DEBUG("onOpen");
    return m->openCarte(s);
}

CEGUI::String Console::onQuit(const CEGUI::String& s) {
    (void)s;
    LOG_DEBUG("onQuit");
    return "";
}

}
