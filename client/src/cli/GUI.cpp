#include "cli/GUI.hpp"

#include <cli/Modele.hpp>
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"
#include "cli/Console.hpp"

#include "cce/Carte.hpp"
#include "cce/Modele.hpp"
#include "cli/Modele.hpp"
#include "CEGUI/CEGUIScriptModule.h"
#include "CEGUI/elements/CEGUIScrollbar.h"

using namespace cli;

GUI::GUI(const string& conteneur_) : cce::GUI(conteneur_)
{
  
}

GUI::~GUI()
{

}

void GUI::init(Modele* modele)
{
    std::string conteneur = "Editeur";

    cce::GUI::init(modele);
    
    console = new cli::Console(conteneur,modele);
}


cce::Console *GUI::getConsole(){
  return console;
}
