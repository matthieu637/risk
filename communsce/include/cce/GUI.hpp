#ifndef CCE_GUI_HPP
#define CCE_GUI_HPP

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUIWindow.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

///
///\file GUI.hpp
///\brief Classe regroupant la gestion de CEGUI
///\author matthieu
///

using std::string;

namespace cce {

class GUI
{

public:
    GUI(const string& conteneur);
    void dessiner();
    bool captureEvent(const sf::Event& event);
    void tocHorloge();
    void init(CEGUI::ScriptModule* module);
    CEGUI::Window* getRootWindow() const;

private:
    
    void initialiserCastEvent();
    void initialiserRessources();
    void chargerRessources();
    CEGUI::Key::Scan toCEGUIKey(const sf::Keyboard::Key& Code) const;
    CEGUI::MouseButton toCEGUIMouseButton(const sf::Mouse::Button& Button) const;

private:
    CEGUI::Window *rootW;
    CEGUI::System *cSys;
    sf::Clock horloge;

    typedef std::map<sf::Keyboard::Key, CEGUI::Key::Scan> ToucheCast;
    typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> SourisCast;

    ToucheCast keys;
    SourisCast mouses;
    
    string conteneur;
};

}

#endif // CCE_GUI_HPP
