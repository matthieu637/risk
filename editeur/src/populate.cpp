#include <iostream>
#include <cce/Tile.hpp>
#include <edt/Repere.hpp>
#include "cce/DaGame.hpp"
#include "bib/XMLEngine.hpp"
#include "cce/Univers.hpp"
#include "cce/TileTemplate.hpp"
#include "cce/ImageManager.hpp"

using namespace cce;

void createXMLModel()
{
    cce::TileTemplate tt;
    tt.init(1000000000, false, "texture13.png");
    
    cce::Univers u;
    bib::XMLEngine::save<cce::Univers>(u, "Univers","data/sf.univ");
    
}
