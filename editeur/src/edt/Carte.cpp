#include "edt/Carte.hpp"
#include "edt/Repere.hpp"
#include "cce/Carte.hpp"


using namespace edt;

Carte::Carte(int x, int y)
{
    repere = edt::Repere(x,y);
}

Carte::Carte()
{
  
}
