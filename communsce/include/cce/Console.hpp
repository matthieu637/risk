#ifndef CCE_CONSOLE_HPP
#define CCE_CONSOLE_HPP

#include <CEGUI/CEGUIcolour.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <CEGUI/CEGUIString.h>
#include <CEGUI/CEGUIWindow.h>
#include <string>
#include <functional>
#include <map>
#include <list>
#include <deque>

using std::string;


namespace cce{

  class Console
  {
    public:
       Console();                  
       void setVisible(bool visible);         
       bool isVisible();                     
       void afficherCommande(CEGUI::String s);
       typedef void (EventConsole)(const string&);
       
    private:
       void RegisterHandlers();                                   
       bool Handle_TextSubmitted(const CEGUI::EventArgs &e);      
       bool Handle_SendButtonPressed(const CEGUI::EventArgs &e);     
       bool Handle_ButtonKeyPressed(const CEGUI::EventArgs &e);
       void ParseText(CEGUI::String inMsg);                       
       void OutputText(CEGUI::String inMsg,                       
		       CEGUI::colour colour = CEGUI::colour( 0xFFFFFFFF)); 
       CEGUI::String onHelp(CEGUI::String s);
 
       CEGUI::Window *m_ConsoleWindow;                            // This will be a pointer to the Console window.
      int index;// index pour pouvoir recuperer l'historique du chat
   
  protected:
    std::map <std::string, std::function<CEGUI::String(CEGUI::String)> > mapCommandes; 
    std::deque <std::string> commandeHistorique;
      
  };

}
#endif // CCE_CCONSOLE_HPP