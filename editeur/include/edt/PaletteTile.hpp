#ifndef PALETTETILE_HPP
#define PALETTETILE_HPP

#include "cce/Palette.hpp"

namespace edt{

class PaletteTile : public cce::Palette
{

public:
PaletteTile();
virtual ~PaletteTile();
void init(cce::GUI const *gui, const std::string& conteneur);
};

}

#endif // PALETTETILE_HPP
