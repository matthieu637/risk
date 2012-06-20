#include "edt/PaletteTile.hpp"
#include "cce/Univers.hpp"
#include "cce/TileTemplate.hpp"
#include <map>
#include <string>
#include <sstream>
#include <CEGUI/CEGUIImageset.h>

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

void PaletteTile::init(const cce::GUI *gui, const string& conteneur, string nom)
{
    Palette::init(gui, conteneur, nom);
    fenetre->setSize(UVector2(UDim(0.0f,333), UDim(0.0f,600)));
    Window *gJumpBtnWindow = NULL;
    ostringstream oss;
    Imageset* ButtonImageset;
    map<int, cce::TileTemplate>::iterator it = cce::Univers::getInstance()->getMapTile()->begin();
    int i=0, j=0;
    
    for (; it != cce::Univers::getInstance()->getMapTile()->end(); it++){
	ButtonImageset = &ImagesetManager::getSingleton().createFromImageFile((*it).second.getPath(), "../../texture/" + (*it).second.getPath());
	oss << (*it).second.getID();
	gJumpBtnWindow = WindowManager::getSingleton().createWindow("TaharezLook/Button",oss.str());  // Create Window
	gJumpBtnWindow->setPosition(UVector2(UDim(0,i*105),UDim(0,j*59)));
	gJumpBtnWindow->setSize(UVector2(UDim(0,105),UDim(0,59)));
	gJumpBtnWindow->setProperty("NormalImage", "set:" + (*it).second.getPath() + " image:full_image");
	gJumpBtnWindow->setProperty("HoverImage", "set:" + (*it).second.getPath() + " image:full_image");
	gJumpBtnWindow->setProperty("PushedImage", "set:" + (*it).second.getPath() + " image:full_image");
	gJumpBtnWindow->setProperty("DisabledImage", "set:" + (*it).second.getPath() + " image:full_image");
	fenetre->addChildWindow(gJumpBtnWindow);
	if(i == 2){
	  j++;
	  i = 0;
	}
	else
	  i++;
    }
}

}