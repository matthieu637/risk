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

void PaletteTile::init(const cce::GUI *gui)
{
    Palette::init(gui);
    
    map<int, cce::TileTemplate>::iterator it = cce::Univers::getInstance()->getMapTile()->begin();
    for (; it != cce::Univers::getInstance()->getMapTile()->end(); it++)
	;
}

}