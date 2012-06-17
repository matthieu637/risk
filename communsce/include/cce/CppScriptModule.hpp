#ifndef CCE_CPPSCRIPTMODULE_HPP
#define CCE_CPPSCRIPTMODULE_HPP

#include <CEGUI/CEGUIScriptModule.h>
#include <map>
#include <functional>

namespace cce {

class CppScriptModule : public CEGUI::ScriptModule
{

public:
    virtual CEGUI::Event::Connection subscribeEvent(CEGUI::EventSet* target, const CEGUI::String& name, CEGUI::Event::Group group, const CEGUI::String& subscriber_name);
    virtual CEGUI::Event::Connection subscribeEvent(CEGUI::EventSet* target, const CEGUI::String& name, const CEGUI::String& subscriber_name);
    virtual void executeString(const CEGUI::String& str);
    virtual bool executeScriptedEventHandler(const CEGUI::String& handler_name, const CEGUI::EventArgs& e);
    virtual int executeScriptGlobal(const CEGUI::String& function_name);
    virtual void executeScriptFile(const CEGUI::String& filename, const CEGUI::String& resourceGroup = "");
    void ajouterHandler(const CEGUI::String& nom_event, CEGUI::Event::Subscriber fonction);
    
private:
    bool doNothing(const CEGUI::EventArgs& e);
    
private:
    std::map<CEGUI::String, CEGUI::Event::Subscriber> actions;
};

}

#endif // CCE_CPPSCRIPTMODULE_HPP
