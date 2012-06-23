#include "edt/PaletteTile.hpp"
#include "cce/Univers.hpp"
#include "cce/TileTemplate.hpp"
#include "edt/Modele.hpp"
#include <CEGUI/CEGUIImageset.h>
#include <CEGUI/CEGUIEvent.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <CEGUI/CEGUISubscriberSlot.h>
#include <CEGUI/elements/CEGUIPushButton.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <map>
#include <string>
#include <sstream>

using std::ostringstream;
using std::string;
using namespace CEGUI;

namespace edt{

PaletteTile::PaletteTile() : Palette()
{

}

PaletteTile::~PaletteTile()
{

}

void PaletteTile::init(const cce::GUI *gui, const string& conteneur, string nom, Modele* _m)
{
    Palette::init(gui, conteneur, nom);
    fenetre->setText("Palette de Tiles");
    m = _m;
    
    ostringstream oss;
    PushButton *tileButton = NULL;
    int i=0, j=0;
    map<int, cce::TileTemplate>::iterator it = cce::Univers::getInstance()->getMapTile()->begin();
    string prop;
    
    for (; it != cce::Univers::getInstance()->getMapTile()->end(); it++){
	prop = "set:" + (*it).second.getPath() + " image:full_image";
	ImagesetManager::getSingleton().createFromImageFile((*it).second.getPath(), "../../texture/" + (*it).second.getPath());
	oss.str("");
	oss << (*it).second.getID();
	tileButton = static_cast<PushButton*>(WindowManager::getSingleton().createWindow("TaharezLook/Button",oss.str()));  // Create Window
	tileButton->setPosition(UVector2(UDim(0,i*105),UDim(0,j*59)));
	tileButton->setSize(UVector2(UDim(0,105),UDim(0,59)));
	tileButton->setProperty("NormalImage", prop);
	tileButton->setProperty("HoverImage", prop);
	tileButton->setProperty("PushedImage", prop);
	tileButton->setProperty("DisabledImage", prop);
	tileButton->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&PaletteTile::setTile,this));
	fenetre->addChildWindow(tileButton);
	if(i == 2){
	  j++;
	  i = 0;
	}
	else
	  i++;
    }
}

bool PaletteTile::setTile(const EventArgs &e)
{
    const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(e);
    PushButton* pb = static_cast<PushButton*>(wea.window);
    const char* nom = pb->getName().c_str();
    m->setTileTemplate(atoi(nom));
    return true;
}

}