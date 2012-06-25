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
#include <CEGUI/elements/CEGUIScrollbar.h>
#include "bib/Logger.hpp"
#include "cce/Controleur.hpp" //BIND


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
        //CEGUI::System::getSingleton().getGUISheet()->getChild(conteneur)->addChildWindow(m_ConsoleWindow);
        (void) conteneur;
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_ConsoleWindow);
        RegisterHandlers();
    }
    else
    {
        CEGUI::Logger::getSingleton().logEvent("Error: Unable to load the ConsoleWindow from Console.layout");
    }
        
    mapCommandes["help"] = BIND(&Console::onHelp);
    
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
            &Console::Handle_ButtonKeyPressed,  
            this));          
}


void Console::afficherCommande(const string& s){
  setVisible(true);
  CEGUI::Window *w =  CEGUI::System::getSingleton().getGUISheet()->getChild("Console");
  w->getChild("Console/EditBox")->setText(s);;
  //w->
  CEGUI::Editbox *editWindow = static_cast<CEGUI::Editbox*>(w->getChild("Console/EditBox"));
  editWindow->setCaratIndex(editWindow->getMaxTextLength());
}

bool Console::Handle_ButtonKeyPressed(const CEGUI::EventArgs &e)
{
  const CEGUI::KeyEventArgs& keyEvent = static_cast<const CEGUI::KeyEventArgs&>(e);

   if ((CEGUI::Key::ArrowUp == keyEvent.scancode)){  
      CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(m_ConsoleWindow->getChild("Console/ChatBox"));
      if(commandeHistorique.size() == 0)
	return true;
      
      if(index == -1 || index == 0){
	index = commandeHistorique.size()-1;
      }else{
	index--;
      }
      //recuperation du texte
      m_ConsoleWindow->getChild("Console/EditBox")->setText(commandeHistorique.at(index));
      //placement correct du curseur
      CEGUI::Editbox *editWindow = static_cast<CEGUI::Editbox*>(m_ConsoleWindow->getChild("Console/EditBox"));
      editWindow->setCaratIndex(editWindow->getMaxTextLength());
      return true;
      
   }else if ((CEGUI::Key::ArrowDown == keyEvent.scancode)){  
      CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(m_ConsoleWindow->getChild("Console/ChatBox"));
       if(commandeHistorique.size() == 0)
	return true;
       
      if(index == commandeHistorique.size()-1){
	index = 0;
      }else{
	index++;
      }
      //recuperation du texte
      m_ConsoleWindow->getChild("Console/EditBox")->setText(commandeHistorique.at(index));
      //placement correct du curseur
      CEGUI::Editbox *editWindow = static_cast<CEGUI::Editbox*>(m_ConsoleWindow->getChild("Console/EditBox"));
      editWindow->setCaratIndex(editWindow->getMaxTextLength());
      return true;
   }else if ((CEGUI::Key::Escape == keyEvent.scancode)){
      setVisible(false);
      return true;
      
   }else if ((CEGUI::Key::Return == keyEvent.scancode)){
    index = -1;
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
    index = -1;
    CEGUI::String Msg = m_ConsoleWindow->getChild("Console/EditBox")->getText();
    (this)->ParseText(Msg);
    m_ConsoleWindow->getChild("Console/EditBox")->setText("");

    return true;
}

void Console::ParseText(CEGUI::String inMsg)
{
  
    std::string inString = inMsg.c_str();

    if (inString.length() >= 1) 
    {
        if (inString.at(0) == '/') // Check if the first letter is a 'command'
        {
            std::string::size_type commandEnd = inString.find(" ", 1);
            std::string command = inString.substr(1, commandEnd - 1);
            //std::string commandArgs = inString.substr(commandEnd + 1, inString.length() - (commandEnd + 1));
	    std::string commandArgs; 
	    
	    if(inString.find(' ') == inString.npos)
	      commandArgs = "";
	    else
	      commandArgs = inString.substr(commandEnd + 1);
            
            for(std::string::size_type i=0; i < command.length(); i++)
            {
                command[i] = tolower(command[i]);
            }
	    string rep;
	    std::map <std::string, std::function<string(const string&)> >::iterator it;
	    for(it = mapCommandes.begin(); it != mapCommandes.end(); it++)
	    {
		if(it->first == command){
		  if(commandArgs == command){
		      rep = it->second("");
		  }else{
		      rep =   it->second(commandArgs);
		  }
		  (this)->OutputText(inString);
		  (this)->OutputText(rep);
		 commandeHistorique.push_back(inString);
		  //commandeHistorique.insert(inString);
		  break;
		}
	     }
        } 
        else
        {   commandeHistorique.push_back(inString);
            (this)->OutputText(inString); // no commands, just output what they wrote
        }
    }
}

 
string Console::onHelp(const string& s){
   std::string outString = "commande /help pour connaitre les commandes disponibles\n commande /say pour ecrire un message sur la console\n bouton escape pour fermer la console\n bouton enter pour afficher le message sur la console";
  (this)->OutputText(outString,CEGUI::colour(1.0f,0.0f,0.0f));
  return outString;
}


void Console::OutputText(CEGUI::String message, CEGUI::colour colour)
{

    // Get a pointer to the ChatBox so we don't have to use this ugly getChild function everytime.
    CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(m_ConsoleWindow->getChild("Console/ChatBox"));

    //CEGUI::FormattedListboxTextItem *newItem=0; // This will hold the actual text and will be the listbox segment / item
    CEGUI::ListboxTextItem *newItem=0;
    newItem = new CEGUI::ListboxTextItem(message,CEGUI::HTF_WORDWRAP_LEFT_ALIGNED); // Instance the Item with Left
    //   wordwrapped alignmentoutputWindow->getVertScrollbar()->
    newItem->setTextColours(colour); // Set the text color
    outputWindow->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
    
    outputWindow->getVertScrollbar()->setScrollPosition((int)outputWindow->getVertScrollbar()->getDocumentSize());
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
