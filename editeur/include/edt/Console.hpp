#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "cce/Console.hpp"
#include "edt/Modele.hpp"
#include <CEGUI/CEGUIString.h>

namespace edt{

  class Console : public cce::Console
  {
    public:
       Console(const std::string& conteneur,Modele *modele);
       
  private:
    CEGUI::String onSave(CEGUI::String s);
    CEGUI::String onOpen(CEGUI::String s);
    CEGUI::String onQuit(CEGUI::String s);
    CEGUI::String onRedimensionner(CEGUI::String s);
    CEGUI::String onNewMap(CEGUI::String s);
    
    Modele* m;
  };

}
#endif // CONSOLE_HPP