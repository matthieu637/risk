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

string Console::onOpen(const std::string& s) {
    LOG_DEBUG("onOpen");
    return m->openCarte(s);
}

string Console::onQuit(const std::string& s) {
    (void)s;
    LOG_DEBUG("onQuit");
    return "";
}

}
