#include "cli/Console.hpp"
#include "bib/Logger.hpp"
#include "cce/Controleur.hpp" //BIND
#include <cce/Modele.hpp>
#include <iostream>
#include <sstream>
#include <string>


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
    std::istringstream iss(s);
    string id;
    string x;
    string y;
    string player;
    
    std::getline(iss, id, ' ');    
    std::getline(iss, x, ' ');   
    std::getline(iss, y, ' ');
    std::getline(iss, player, ' ');
    
    
    LOG_DEBUG("id = "+id+"  x= "+x+"  y = "+y);
    if(s.find(' ') == s.npos)
        return "vous devez utiliser la commande : /spawn id x y";
    else {
        m->spawnUnit(atoi(id.c_str()),atoi(x.c_str()),atoi(y.c_str()),atoi(player.c_str()));
        return "unité bien spawnée";
    }
}

}
