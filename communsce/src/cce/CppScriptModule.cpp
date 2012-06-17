#include "cce/CppScriptModule.hpp"
#include "bib/Logger.hpp"
#include <CEGUI/CEGUIEventSet.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <functional>

using namespace cce;

CEGUI::Event::Connection CppScriptModule::subscribeEvent(CEGUI::EventSet* target, const CEGUI::String& name, CEGUI::Event::Group group, const CEGUI::String& subscriber_name)
{
    (void) target;
    (void) name;
    (void) group;
    (void) subscriber_name;
    LOG_WARNING("subscribeEvent n'est pas implémenté");
    return nullptr;
}

CEGUI::Event::Connection CppScriptModule::subscribeEvent(CEGUI::EventSet* target, const CEGUI::String& name, const CEGUI::String& subscriber_name)
{
    CEGUI::Event::Subscriber s = actions[subscriber_name];
    if(actions.find(subscriber_name) != actions.end())
        return target->subscribeEvent(name, s);
    else
    {
        LOG_WARNING("pas d'action trouvée pour l'évènement " << subscriber_name << " de type " << name);
        return target->subscribeEvent(name, CEGUI::Event::Subscriber(std::bind(& CppScriptModule::doNothing, this, std::placeholders::_1)));
    }
}

void CppScriptModule::executeString(const CEGUI::String& str)
{
    (void) str;
    LOG_WARNING("executeString n'est pas implémenté");
}

bool CppScriptModule::executeScriptedEventHandler(const CEGUI::String& handler_name, const CEGUI::EventArgs& e)
{
    (void) handler_name;
    (void) e;
    LOG_DEBUG("executeScriptedEventHandler n'est pas implémenté");
    return false;
}

int CppScriptModule::executeScriptGlobal(const CEGUI::String& function_name)
{
    (void) function_name;
    LOG_WARNING("executeScriptGlobal n'est pas implémenté");
    return 0;
}

void CppScriptModule::executeScriptFile(const CEGUI::String& filename, const CEGUI::String& resourceGroup)
{
    (void) filename;
    (void) resourceGroup;
    LOG_WARNING("executeScriptFile n'est pas implémenté");
}

bool CppScriptModule::doNothing(const CEGUI::EventArgs& e)
{
    (void) e;
    return false;
}


void CppScriptModule::ajouterHandler(const CEGUI::String& nom_event, CEGUI::Event::Subscriber fonction) {
    actions[nom_event] = fonction;
}
