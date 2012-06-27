#include "cli/Console.hpp"
#include "bib/Logger.hpp"
#include "cce/Controleur.hpp" //BIND
#include <cce/Modele.hpp>


namespace cli {
Console::Console(Modele *modele) : cce::Console()
{
    mapCommandes["open"] = BIND(&Console::onOpen);
    mapCommandes["quit"] = BIND(&Console::onQuit);
    mapCommandes["spawn"] = BIND(&Console::onSpawn);
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
string Console::onSpawn(const std::string& s) {
    string::size_type argEnd1 = s.find(" ", 1);
    string::size_type argEnd2 = s.find(" ", argEnd1+1);
    string id = s.substr(0, argEnd1);
    string x = s.substr(argEnd1, argEnd2-1);
    string y = s.substr(argEnd2);
    
    LOG_DEBUG("id = "+id+"  x= "+x+"  y = "+y);
    if(s.find(' ') == s.npos)
        return "vous devez utiliser la commande : /spawn id x y";
    else {
        m->spawnUnit(atoi(id.c_str()),atoi(x.c_str()),atoi(y.c_str()));
        return "unité bien spawnée";
    }
}

}
