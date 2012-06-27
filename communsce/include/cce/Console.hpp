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


namespace cce {

class Console
{
public:
    Console();
    void setVisible(bool visible);
    bool isVisible();
    bool getConfirmQuit();
    void OutputText(const string&  inMsg,CEGUI::colour colour = CEGUI::colour( 0xFFFFFFFF));
    typedef void (EventConsole)(const string&);
    void afficherCommande(const string& s);

protected:
    virtual bool Handle_ButtonKeyPressed(const CEGUI::EventArgs &e);
    virtual void ParseText(const CEGUI::String& inMsg);

private:
    void RegisterHandlers();
    bool Handle_TextSubmitted(const CEGUI::EventArgs &e);
    bool Handle_SendButtonPressed(const CEGUI::EventArgs &e);
    bool ignore(const CEGUI::EventArgs& e);
    


    string onHelp(const string& s);

    CEGUI::Window *m_ConsoleWindow;                            // This will be a pointer to the Console window.
    int index;// index pour pouvoir recuperer l'historique du chat

protected:
    std::map <std::string, std::function<string(const string &)> > mapCommandes;
    std::deque <std::string> commandeHistorique;
    bool confirmQuit;
    bool wantQuit;


};

}
#endif // CCE_CCONSOLE_HPP
