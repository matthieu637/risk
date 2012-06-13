#ifndef EDT_CARTE_HPP
#define EDT_CARTE_HPP

#include "cce/Carte.hpp"
#include "Repere.hpp"


namespace edt {

class Carte : public cce::Carte
{

public:
    Carte(int x, int y);
protected:
    Repere repere;
};

}

#endif // EDT_CARTE_HPP
