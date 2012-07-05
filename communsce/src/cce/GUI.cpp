#include "cce/GUI.hpp"
#include <cce/CppScriptModule.hpp>
#include <cce/Modele.hpp>
#include <bib/Logger.hpp>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUI/CEGUIDefaultResourceProvider.h>
#include <CEGUI/CEGUIImageset.h>
#include <CEGUI/CEGUIFont.h>
#include <CEGUI/CEGUIScheme.h>
#include <CEGUI/falagard/CEGUIFalWidgetLookManager.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIScriptModule.h>
#include <CEGUI/CEGUIXMLParser.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <CEGUI/CEGUIFontManager.h>
#include <CEGUI/CEGUIImagesetManager.h>
#include <CEGUI/CEGUIEvent.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <CEGUI/CEGUISubscriberSlot.h>

namespace cce {

using namespace cce;

GUI::GUI(const string& conteneur_):conteneur(conteneur_)
{
    initialiserCastEvent();
}

void GUI::dessiner()
{
    CEGUI::System::getSingleton().renderGUI();
}

void GUI::tocHorloge() {
    cSys->injectTimePulse((float)(horloge.getElapsedTime().asSeconds()));
    horloge.restart();
}

CEGUI::Window* GUI::getRootWindow() const
{
  return rootW;
}

bool GUI::captureEvent(const sf::Event& Event)
{
    switch (Event.type)
    {
    case sf::Event::MouseLeft :
        return cSys->injectMouseLeaves();
    case sf::Event::TextEntered:
        return cSys->injectChar(Event.text.unicode);
    case sf::Event::KeyPressed:
        return cSys->injectKeyDown(toCEGUIKey(Event.key.code));
    case sf::Event::KeyReleased:
        return cSys->injectKeyUp(toCEGUIKey(Event.key.code));
    case sf::Event::MouseMoved:
        return cSys->injectMousePosition(static_cast<float>(Event.mouseMove.x), static_cast<float>(Event.mouseMove.y));
    case sf::Event::MouseButtonPressed:
        return cSys->injectMouseButtonDown(toCEGUIMouseButton(Event.mouseButton.button));
    case sf::Event::MouseButtonReleased:
        return cSys->injectMouseButtonUp(toCEGUIMouseButton(Event.mouseButton.button));
    case sf::Event::MouseWheelMoved:
        return cSys->injectMouseWheelChange(static_cast<float>(Event.mouseWheel.delta));

    default :
        return false;
    }
}


void GUI::setScriptModule(CEGUI::ScriptModule* module) {
    scm=module;
}
void GUI::init(const Modele* modele)
{
    (void) modele;
  
    CEGUI::OpenGLRenderer& myRenderer = CEGUI::OpenGLRenderer::create();
    //CEGUI::OpenGLRenderer& myRenderer = CEGUI:: OpenGLRenderer:: bootstrapSystem ();
    cSys = &CEGUI::System::create( myRenderer );

    initialiserRessources();
    chargerRessources();

    //Events handler
    cSys->setScriptingModule(scm);

    cSys->setDefaultFont("DejaVuSans-10");
    // cSys->setDefaultMouseCursor( "Vanilla", "MouseArrow" );
    cSys->setDefaultMouseCursor( "TaharezLook", "MouseArrow" );
    //cSys->setDefaultTooltip( "Vanilla/Tooltip" );
    cSys->setDefaultTooltip( "TaharezLook/Tooltip" );

    rootW = CEGUI::WindowManager::getSingleton().loadWindowLayout( conteneur );
    cSys->setGUISheet( rootW );
}

void GUI::initialiserRessources() {
    // initialise les répertoires nécessaires au DefaultResourceProvider
    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
                                         (CEGUI::System::getSingleton().getResourceProvider());

    rp->setResourceGroupDirectory("schemes", "data/gui/schemes/");
    rp->setResourceGroupDirectory("imagesets", "data/gui/imagesets/");
    rp->setResourceGroupDirectory("fonts", "data/gui/fonts/");
    rp->setResourceGroupDirectory("layouts", "data/gui/layouts/");
    rp->setResourceGroupDirectory("looknfeels", "data/gui/looknfeel/");
    //rp->setResourceGroupDirectory("lua_scripts", "data/gui/lua_scripts/");

    // ensemble des groupes de ressources à utiliser par défaut
    CEGUI::Imageset::setDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    //CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

    // setup default group for validation schemas
    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");
}

void GUI::chargerRessources() {

    CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");
    CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );
    CEGUI::ImagesetManager::getSingleton().create("TaharezLook.imageset");
}

CEGUI::Key::Scan GUI::toCEGUIKey(const sf::Keyboard::Key& Code) const
{
    if (keys.find(Code) == keys.end())
        return (CEGUI::Key::Scan)0;

    return keys.at(Code);
}

CEGUI::MouseButton GUI::toCEGUIMouseButton(const sf::Mouse::Button& Button) const
{
    if (mouses.find(Button) == mouses.end())
        return (CEGUI::MouseButton)0;

    return mouses.at(Button);
}

cce::Console *GUI::getConsole(){
  LOG_DEBUG("cce gui getConsole");
  return console;
}

void GUI::initialiserCastEvent()
{

    keys[sf::Keyboard::Escape] = CEGUI::Key::Escape ;
    keys[sf::Keyboard::Num1] = CEGUI::Key::One ;
    keys[sf::Keyboard::Num2] = CEGUI::Key::Two ;
    keys[sf::Keyboard::Num3] = CEGUI::Key::Three ;
    keys[sf::Keyboard::Num4] = CEGUI::Key::Four ;
    keys[sf::Keyboard::Num5] = CEGUI::Key::Five ;
    keys[sf::Keyboard::Num6] = CEGUI::Key::Six ;
    keys[sf::Keyboard::Num7] = CEGUI::Key::Seven ;
    keys[sf::Keyboard::Num8] = CEGUI::Key::Eight ;
    keys[sf::Keyboard::Num9] = CEGUI::Key::Nine ;
    keys[sf::Keyboard::Num0] = CEGUI::Key::Zero ;
    keys[sf::Keyboard::Dash] = CEGUI::Key::Minus ;
    keys[sf::Keyboard::Equal] = CEGUI::Key::Equals ;
    keys[sf::Keyboard::BackSpace] = CEGUI::Key::Backspace ;
    keys[sf::Keyboard::Tab] = CEGUI::Key::Tab ;
    keys[sf::Keyboard::Q] = CEGUI::Key::Q ;
    keys[sf::Keyboard::W] = CEGUI::Key::W ;
    keys[sf::Keyboard::E] = CEGUI::Key::E ;
    keys[sf::Keyboard::R] = CEGUI::Key::R ;
    keys[sf::Keyboard::T] = CEGUI::Key::T ;
    keys[sf::Keyboard::Y] = CEGUI::Key::Y ;
    keys[sf::Keyboard::U] = CEGUI::Key::U ;
    keys[sf::Keyboard::I] = CEGUI::Key::I ;
    keys[sf::Keyboard::O] = CEGUI::Key::O ;
    keys[sf::Keyboard::P] = CEGUI::Key::P ;
    keys[sf::Keyboard::LBracket] = CEGUI::Key::LeftBracket ;
    keys[sf::Keyboard::RBracket] = CEGUI::Key::RightBracket ;
    keys[sf::Keyboard::Return] = CEGUI::Key::Return ;
    keys[sf::Keyboard::LControl] = CEGUI::Key::LeftControl ;
    keys[sf::Keyboard::A] = CEGUI::Key::A ;
    keys[sf::Keyboard::S] = CEGUI::Key::S ;
    keys[sf::Keyboard::D] = CEGUI::Key::D ;
    keys[sf::Keyboard::F] = CEGUI::Key::F ;
    keys[sf::Keyboard::G] = CEGUI::Key::G ;
    keys[sf::Keyboard::H] = CEGUI::Key::H ;
    keys[sf::Keyboard::J] = CEGUI::Key::J ;
    keys[sf::Keyboard::K] = CEGUI::Key::K ;
    keys[sf::Keyboard::L] = CEGUI::Key::L ;
    keys[sf::Keyboard::SemiColon] = CEGUI::Key::Semicolon ;
    keys[sf::Keyboard::LShift] = CEGUI::Key::LeftShift ;
    keys[sf::Keyboard::BackSlash] = CEGUI::Key::Backslash ;
    keys[sf::Keyboard::Z] = CEGUI::Key::Z ;
    keys[sf::Keyboard::X] = CEGUI::Key::X ;
    keys[sf::Keyboard::C] = CEGUI::Key::C ;
    keys[sf::Keyboard::V] = CEGUI::Key::V ;
    keys[sf::Keyboard::B] = CEGUI::Key::B ;
    keys[sf::Keyboard::N] = CEGUI::Key::N ;
    keys[sf::Keyboard::M] = CEGUI::Key::M ;
    keys[sf::Keyboard::Comma] = CEGUI::Key::Comma ;
    keys[sf::Keyboard::Period] = CEGUI::Key::Period ;
    keys[sf::Keyboard::Slash] = CEGUI::Key::Slash ;
    keys[sf::Keyboard::RShift] = CEGUI::Key::RightShift ;
    keys[sf::Keyboard::Multiply] = CEGUI::Key::Multiply ;
    keys[sf::Keyboard::LAlt] = CEGUI::Key::LeftAlt ;
    keys[sf::Keyboard::Space] = CEGUI::Key::Space ;
    keys[sf::Keyboard::F1] = CEGUI::Key::F1 ;
    keys[sf::Keyboard::F2] = CEGUI::Key::F2 ;
    keys[sf::Keyboard::F3] = CEGUI::Key::F3 ;
    keys[sf::Keyboard::F4] = CEGUI::Key::F4 ;
    keys[sf::Keyboard::F5] = CEGUI::Key::F5 ;
    keys[sf::Keyboard::F6] = CEGUI::Key::F6 ;
    keys[sf::Keyboard::F7] = CEGUI::Key::F7 ;
    keys[sf::Keyboard::F8] = CEGUI::Key::F8 ;
    keys[sf::Keyboard::F9] = CEGUI::Key::F9 ;
    keys[sf::Keyboard::F10] = CEGUI::Key::F10 ;
    keys[sf::Keyboard::Numpad7] = CEGUI::Key::Numpad7 ;
    keys[sf::Keyboard::Numpad8] = CEGUI::Key::Numpad8 ;
    keys[sf::Keyboard::Numpad9] = CEGUI::Key::Numpad9 ;
    keys[sf::Keyboard::Subtract] = CEGUI::Key::Subtract ;
    keys[sf::Keyboard::Numpad4] = CEGUI::Key::Numpad4 ;
    keys[sf::Keyboard::Numpad5] = CEGUI::Key::Numpad5 ;
    keys[sf::Keyboard::Numpad6] = CEGUI::Key::Numpad6 ;
    keys[sf::Keyboard::Add] = CEGUI::Key::Add ;
    keys[sf::Keyboard::Numpad1] = CEGUI::Key::Numpad1 ;
    keys[sf::Keyboard::Numpad2] = CEGUI::Key::Numpad2 ;
    keys[sf::Keyboard::Numpad3] = CEGUI::Key::Numpad3 ;
    keys[sf::Keyboard::Numpad0] = CEGUI::Key::Numpad0 ;
    keys[sf::Keyboard::F11] = CEGUI::Key::F11 ;
    keys[sf::Keyboard::F12] = CEGUI::Key::F12 ;
    keys[sf::Keyboard::F13] = CEGUI::Key::F13 ;
    keys[sf::Keyboard::F14] = CEGUI::Key::F14 ;
    keys[sf::Keyboard::F15] = CEGUI::Key::F15 ;
    keys[sf::Keyboard::RControl] = CEGUI::Key::RightControl ;
    keys[sf::Keyboard::Divide] = CEGUI::Key::Divide ;
    keys[sf::Keyboard::RAlt] = CEGUI::Key::RightAlt ;
    keys[sf::Keyboard::Pause] = CEGUI::Key::Pause ;
    keys[sf::Keyboard::Home] = CEGUI::Key::Home ;
    keys[sf::Keyboard::Up] = CEGUI::Key::ArrowUp ;
    keys[sf::Keyboard::PageUp] = CEGUI::Key::PageUp ;
    keys[sf::Keyboard::Left] = CEGUI::Key::ArrowLeft ;
    keys[sf::Keyboard::Right] = CEGUI::Key::ArrowRight ;
    keys[sf::Keyboard::End] = CEGUI::Key::End ;
    keys[sf::Keyboard::Down] = CEGUI::Key::ArrowDown ;
    keys[sf::Keyboard::PageDown] = CEGUI::Key::PageDown ;
    keys[sf::Keyboard::Insert] = CEGUI::Key::Insert ;
    keys[sf::Keyboard::Delete] = CEGUI::Key::Delete ;

    mouses[sf::Mouse::Left]	= CEGUI::LeftButton;
    mouses[sf::Mouse::Middle]	= CEGUI::MiddleButton;
    mouses[sf::Mouse::Right]	= CEGUI::RightButton;
    mouses[sf::Mouse::XButton1]	= CEGUI::X1Button;
    mouses[sf::Mouse::XButton2]	= CEGUI::X2Button;
}

}

