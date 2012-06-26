#include "edt/Console.hpp"
#include "bib/Logger.hpp"
#include "cce/Controleur.hpp" //BIND
#include <cce/Modele.hpp>
#include <bib/StringUtils.hpp>
#include <edt/Repere.hpp>

namespace edt {
  Console::Console(const std::string& conteneur,Modele *modele) : cce::Console(conteneur)
{ 

  mapCommandes["save"] = BIND(&Console::onSave);
  mapCommandes["open"] = BIND(&Console::onOpen);
  mapCommandes["quit"] = BIND(&Console::onQuit);
  mapCommandes["redimensionner"] = BIND(&Console::onRedimensionner);
  mapCommandes["new_map"] = BIND(&Console::onNewMap);
  m = modele;
  // mapCommandes["say"] = BIND(&Console::onSay); 
}


CEGUI::String Console::onSave(CEGUI::String s){
  if (s == "" || bib::onlySpaceCharacter(s.c_str())){
   return m->saveCarte();  
  }else{
    return m->saveCarte(s);
  }
}

CEGUI::String Console::onOpen(CEGUI::String s){
   LOG_DEBUG("onOpen "+s);
  return m->openCarte(s);
}

CEGUI::String Console::onNewMap(CEGUI::String s){
 (void) s;
  m->nouvelleCarte();
  return "Nouvelle carte affichée";
}

CEGUI::String Console::onRedimensionner(CEGUI::String s){
  
   CEGUI::String::size_type argEnd = s.find(" ", 1);
   CEGUI::String x = s.substr(0, argEnd);
   CEGUI::String y = s.substr(argEnd + 1); 

  if(s.find(' ') == s.npos)
    return "vous devez utiliser la commande : /redimensionner x y";
  else{
    edt::Repere* r = static_cast<edt::Repere*> (m->getCarte()->getRepere());
    r->redimensionner(atoi(x.c_str()), atoi(y.c_str()));
    return "Carte redimensionnée aux dimensions ";
 }
}

CEGUI::String Console::onQuit(CEGUI::String s){
  (void)s;
  LOG_DEBUG("onQuit");
  return "";
}

}