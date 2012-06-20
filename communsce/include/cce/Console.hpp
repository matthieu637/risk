#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <CEGUI/CEGUIcolour.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <CEGUI/CEGUIString.h>
#include <CEGUI/CEGUIWindow.h>
#include <string>
#include <map>
using std::string;
//using std::map;

namespace cce{

  class Console
  {
    public:
       Console(const std::string& conteneur);                  
       void setVisible(bool visible);         
       bool isVisible();                     
       void afficherCommande(const string& s);
       typedef void (EventConsole)(const string&);
       
    private:
       void RegisterHandlers();                                   
       bool Handle_TextSubmitted(const CEGUI::EventArgs &e);      
       bool Handle_SendButtonPressed(const CEGUI::EventArgs &e);     
       bool Handle_ButtonKeyPressed(const CEGUI::EventArgs &e);
       void ParseText(CEGUI::String inMsg);                       
       void OutputText(CEGUI::String inMsg,                       
		       CEGUI::colour colour = CEGUI::colour( 0xFFFFFFFF)); 
       void onHelp(const string& s);
 
       CEGUI::Window *m_ConsoleWindow;                            // This will be a pointer to the Console window.
      int index;// index pour pouvoir recuperer l'historique du chat
      std::map<CEGUI::String, EventConsole*> mapCommandes;

      
  };

}
#endif // CONSOLE_HPP