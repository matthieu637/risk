#include "edt/Console.hpp"
#include "bib/Logger.hpp"
#include "cce/Controleur.hpp" //BIND
#include <cce/Modele.hpp>
#include <bib/StringUtils.hpp>


namespace edt {
  Console::Console(const std::string& conteneur,Modele *modele) : cce::Console(conteneur)
{ 

  mapCommandes["save"] = BIND(&Console::onSave);
  mapCommandes["open"] = BIND(&Console::onOpen);
  mapCommandes["quit"] = BIND(&Console::onQuit);
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

string Console::onQuit(const string& s){
  (void)s;
  LOG_DEBUG("onQuit");
  return "";
}

}