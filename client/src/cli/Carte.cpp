#include "cli/Carte.hpp"
#include "cli/CoucheDecor.hpp"
#include "cce/Carte.hpp"

namespace cli{

Carte::Carte()
{
    couche_decor = cli::CoucheDecor();
}

Carte::~Carte()
{

}

}