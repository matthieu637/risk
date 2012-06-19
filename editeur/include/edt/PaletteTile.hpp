#ifndef PALETTETILE_HPP
#define PALETTETILE_HPP

#include "edt/Palette.hpp"



namespace edt{

class PaletteTile : public Palette
{

public:
PaletteTile();
virtual ~PaletteTile();
void init(GUI const *gui, string nom);
};

}

#endif // PALETTETILE_HPP
