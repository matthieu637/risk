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
       void afficherCommande(const string& s);
       bool getConfirmQuit();
       void OutputText(const string&  inMsg,CEGUI::colour colour = CEGUI::colour( 0xFFFFFFFF)); 
       typedef void (EventConsole)(const string&);
       
    private:
       void RegisterHandlers();                                   
       bool Handle_TextSubmitted(const CEGUI::EventArgs &e);      
       bool Handle_SendButtonPressed(const CEGUI::EventArgs &e);     
       bool Handle_ButtonKeyPressed(const CEGUI::EventArgs &e);
       bool ignore(const CEGUI::EventArgs& e);
       void ParseText(CEGUI::String inMsg);                       
       
       string onHelp(const string& s);
 
       CEGUI::Window *m_ConsoleWindow;                            // This will be a pointer to the Console window.
      int index;// index pour pouvoir recuperer l'historique du chat
   
  protected:
    std::map <std::string, std::function<string(const string &)> > mapCommandes; 
    std::deque <std::string> commandeHistorique;
    bool confirmQuit;
   
      
  };

}
#endif // CCE_CCONSOLE_HPP