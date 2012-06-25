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
  m = modele;
  // mapCommandes["say"] = BIND(&Console::onSay); 
}


string Console::onSave(const string& s){
  if (s == "" || bib::onlySpaceCharacter(s)){
   return m->saveCarte();  
  }else{
    return m->saveCarte(s);
  }
}

string Console::onOpen(const string& s){
   LOG_DEBUG("onOpen");
  return m->openCarte(s);
}

string Console::onRedimensionner(const string& s){
  
   std::string::size_type argEnd = s.find(" ", 1);
   std::string x = s.substr(0, argEnd);
   std::string y = s.substr(argEnd + 1); 

  if(s.find(' ') == s.npos)
    return "vous devez utiliser la commande : /redimensionner x y";
  else{
    edt::Repere* r = static_cast<edt::Repere*> (m->getCarte()->getRepere());
    r->redimensionner(atoi(x.c_str()), atoi(y.c_str()));
    return "Carte redimensionnée aux dimensions " + x+ "x" + y;
}
}

string Console::onQuit(const string& s){
  (void)s;
  LOG_DEBUG("onQuit");
  return "";
}

}