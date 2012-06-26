#include "cli/Console.hpp"
#include "bib/Logger.hpp"
#include "cce/Controleur.hpp" //BIND
#include <cce/Modele.hpp>


namespace cli {
Console::Console(const std::string& conteneur,Modele *modele) : cce::Console(conteneur)
{
    mapCommandes["open"] = BIND(&Console::onOpen);
    mapCommandes["quit"] = BIND(&Console::onQuit);
    m = modele;
}

string Console::onOpen(const string& s) {
    LOG_DEBUG("onOpen");
    return m->openCarte(s);
}

string Console::onQuit(const string& s) {
    (void)s;
    LOG_DEBUG("onQuit");
    return "";
}

}