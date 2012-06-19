#include "cce/Console.hpp"
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUILogger.h>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUIEvent.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <CEGUI/CEGUIString.h>
#include <CEGUI/elements/CEGUIListbox.h>
#include <CEGUI/elements/CEGUIPushButton.h>
#include <CEGUI/elements/CEGUIEditbox.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
#include <string>
#include "bib/Logger.hpp"



namespace cce {

Console::Console(const std::string& conteneur)
{
    // Get a local pointer to the CEGUI Window Manager, Purely for convenience to reduce typing
    CEGUI::WindowManager *pWindowManager = CEGUI::WindowManager::getSingletonPtr();

    m_ConsoleWindow = pWindowManager->loadWindowLayout("Console.layout");

    // Being a good programmer, its a good idea to ensure that we got a valid window back.
    if (m_ConsoleWindow)
    {
        // Lets add our new window to the Root GUI Window
        CEGUI::System::getSingleton().getGUISheet()->getChild(conteneur)->addChildWindow(m_ConsoleWindow);
        RegisterHandlers();
    }
    else
    {
        CEGUI::Logger::getSingleton().logEvent("Error: Unable to load the ConsoleWindow from Console.layout");
    }
}

void Console::RegisterHandlers()
{
    m_ConsoleWindow->getChild("Console/SendButton")->subscribeEvent(
        CEGUI::PushButton::EventClicked,  
        CEGUI::Event::Subscriber(    
            &Console::Handle_SendButtonPressed,  
            this));            
    
     m_ConsoleWindow->getChild("Console/EditBox")->subscribeEvent(
	CEGUI::PushButton::EventKeyDown,
        CEGUI::Event::Subscriber(    
            &Console::Handle_SendButtonKeyPressed,  
            this));                            

}


bool Console::Handle_TextSubmitted(const CEGUI::EventArgs &e)
{
    const CEGUI::WindowEventArgs* args = static_cast<const CEGUI::WindowEventArgs*>(&e);
    CEGUI::String Msg = m_ConsoleWindow->getChild("Console/EditBox")->getText();
    (this)->ParseText(Msg);

    m_ConsoleWindow->getChild("Console/EditBox")->setText("");

    return true;
}

bool Console::Handle_SendButtonKeyPressed(const CEGUI::EventArgs &e)
{
  const CEGUI::KeyEventArgs& keyEvent = static_cast<const CEGUI::KeyEventArgs&>(e);

   if ((CEGUI::Key::Return == keyEvent.scancode)){
    
    CEGUI::String Msg = m_ConsoleWindow->getChild("Console/EditBox")->getText();
    (this)->ParseText(Msg);
    m_ConsoleWindow->getChild("Console/EditBox")->setText("");

    return true;
   }
   return false;
}

bool Console::Handle_SendButtonPressed(const CEGUI::EventArgs &e)
{
    (void) e;
    CEGUI::String Msg = m_ConsoleWindow->getChild("Console/EditBox")->getText();
    (this)->ParseText(Msg);
    m_ConsoleWindow->getChild("Console/EditBox")->setText("");

    return true;
}

void Console::ParseText(CEGUI::String inMsg)
{

    // I personally like working with std::string. So i'm going to convert it here.
    std::string inString = inMsg.c_str();

    if (inString.length() >= 1) // Be sure we got a string longer than 0
    {
        if (inString.at(0) == '/') // Check if the first letter is a 'command'
        {
            std::string::size_type commandEnd = inString.find(" ", 1);
            std::string command = inString.substr(1, commandEnd - 1);
            std::string commandArgs = inString.substr(commandEnd + 1, inString.length() - (commandEnd + 1));
            //convert command to lower case
            for(std::string::size_type i=0; i < command.length(); i++)
            {
                command[i] = tolower(command[i]);
            }

            // Begin processing

            if (command == "say")
            {
                std::string outString = "You:" + inString; // Append our 'name' to the message we'll display in the list
                // mConsole->OutputText(outString);
            }
            else if (command == "quit")
            {
                // do a /quit
            }
            else if (command == "help")
            {
                // do a /help
            }
            else
            {
                std::string outString = "<" + inString + "> is an invalid command.";
                (this)->OutputText(outString,CEGUI::colour(1.0f,0.0f,0.0f)); // With red ANGRY colors!
            }
        } // End if /
        else
        {
            (this)->OutputText(inString); // no commands, just output what they wrote
        }
    }
}

void Console::OutputText(CEGUI::String message, CEGUI::colour colour)
{

    // Get a pointer to the ChatBox so we don't have to use this ugly getChild function everytime.
    CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(m_ConsoleWindow->getChild("Console/ChatBox"));

    //CEGUI::FormattedListboxTextItem *newItem=0; // This will hold the actual text and will be the listbox segment / item
    CEGUI::ListboxTextItem *newItem=0;
    newItem = new CEGUI::ListboxTextItem(message,CEGUI::HTF_WORDWRAP_LEFT_ALIGNED); // Instance the Item with Left
    //   wordwrapped alignment
    newItem->setTextColours(colour); // Set the text color
    outputWindow->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
}

void Console::setVisible(bool visible)
{
    m_ConsoleWindow->setVisible(visible);
}

bool Console::isVisible()
{
    return m_ConsoleWindow->isVisible();
}


}
