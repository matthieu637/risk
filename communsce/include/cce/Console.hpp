#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <CEGUI/CEGUIcolour.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <CEGUI/CEGUIString.h>
#include <CEGUI/CEGUIWindow.h>

namespace cce{

  class Console
  {
    public:
       Console();                   // Constructor
       void setVisible(bool visible);         // Hide or show the console
       bool isVisible();                      // return true if console is visible, false if is hidden
 
    private:
       void CreateCEGUIWindow();                                  // The function which will load in the CEGUI Window and register event handlers
       void RegisterHandlers();                                   // Register our handler functions
       bool Handle_TextSubmitted(const CEGUI::EventArgs &e);      // Handle when we press Enter after typing
       bool Handle_SendButtonPressed(const CEGUI::EventArgs &e);  // Handle when we press the Send button         
       void ParseText(CEGUI::String inMsg);                       // Parse the text the user submitted.
       void OutputText(CEGUI::String inMsg,                       // Post the message to the ChatHistory listbox.
		       CEGUI::colour colour = CEGUI::colour( 0xFFFFFFFF)); //   with a white color default
 
       CEGUI::Window *m_ConsoleWindow;                            // This will be a pointer to the ConsoleRoot window.
       CEGUI::String sNamePrefix;                                  // This will be the prefix name we give the layout
       bool m_bConsole; 
       CEGUI::Window *mWindow; // type a verifier
    
  };

}
#endif // CONSOLE_HPP