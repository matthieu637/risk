#ifndef PALETTETILE_HPP
#define PALETTETILE_HPP

#include "cce/Palette.hpp"

namespace edt{
  
class Modele;

class PaletteTile : public cce::Palette
{

public:
    PaletteTile();
    virtual ~PaletteTile();

    void init(cce::GUI const *gui, string nom, Modele* _m);
    bool setTile(const CEGUI::EventArgs &e);

private:
    Modele* m;
};

}

#endif // PALETTETILE_HPP
