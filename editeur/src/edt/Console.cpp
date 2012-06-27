#include "edt/Console.hpp"
#include "bib/Logger.hpp"
#include "cce/Controleur.hpp" //BIND
#include <cce/Modele.hpp>
#include <bib/StringUtils.hpp>
#include <edt/Repere.hpp>

namespace edt {
Console::Console(Modele *modele) : cce::Console()
{

    mapCommandes["save"] = BIND(&Console::onSave);
    mapCommandes["open"] = BIND(&Console::onOpen);
    mapCommandes["quit"] = BIND(&Console::onQuit);
    mapCommandes["redimensionner"] = BIND(&Console::onRedimensionner);
    mapCommandes["new_map"] = BIND(&Console::onNewMap);
    m = modele;
    // mapCommandes["say"] = BIND(&Console::onSay);
}


string Console::onSave(const string& s) {
    if (s == "" || bib::onlySpaceCharacter(s.c_str())) {
        return m->saveCarte();
    } else {
        return m->saveCarte(s);
    }
}

string Console::onOpen(const string& s) {
    return m->openCarte(s);
}

string Console::onNewMap(const string& s) {
    (void) s;
    m->nouvelleCarte();
    return "Nouvelle carte affichée";
}

string Console::onRedimensionner(const string& s) {

    string::size_type argEnd = s.find(" ", 1);
    string x = s.substr(0, argEnd);
    string y = s.substr(argEnd + 1);

    if(s.find(' ') == s.npos)
        return "vous devez utiliser la commande : /redimensionner x y";
    else {
        m->redimensionner(atoi(x.c_str()), atoi(y.c_str()));
        return "Carte redimensionnée aux dimensions ";
    }
}

string Console::onQuit(const string& s) {
    (void)s;
    wantQuit = true;
    m->quit();
    return "Voulez vous vraiment quitter? y/n";
}

void Console::ParseText(const CEGUI::String& inMsg)
{
    cce::Console::ParseText(inMsg);

    if(inMsg == "y" && wantQuit) {
        confirmQuit=true;
        m->quit();
    }else if(inMsg != "/quit")
      wantQuit = false;
}

}
