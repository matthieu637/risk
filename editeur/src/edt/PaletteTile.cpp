#include "edt/PaletteTile.hpp"
#include "cce/Univers.hpp"
#include "cce/TileTemplate.hpp"
#include <map>

namespace edt{

PaletteTile::PaletteTile() : Palette()
{

}

PaletteTile::~PaletteTile()
{

}

void PaletteTile::init(GUI const *gui, string nom)
{
    Palette::init(gui, nom);
    
    map<int, cce::TileTemplate>::iterator it = cce::Univers::getInstance()->getMapTile()->begin();
    for (; it != cce::Univers::getInstance()->getMapTile()->end(); it++)
	;
}

}