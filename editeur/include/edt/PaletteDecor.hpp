#ifndef PALETTEDECOR_HPP
#define PALETTEDECOR_HPP

#include "cce/Palette.hpp"

namespace edt{
  
class Modele;

class PaletteDecor : public cce::Palette
{

public:
    PaletteDecor();
    virtual ~PaletteDecor();

    void init(cce::GUI const *gui, const std::string& conteneur, string nom, Modele* _m);
    bool setDecor(const CEGUI::EventArgs &e);

private:
    Modele* m;
};

}

#endif // PALETTEDECOR_HPP
