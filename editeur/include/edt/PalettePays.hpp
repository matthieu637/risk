#ifndef PALETTEPAYS_HPP
#define PALETTEPAYS_HPP

#include "cce/Palette.hpp"
#include <string>

using std::string;

namespace CEGUI{
class PushButton;
}

namespace edt{

class Carte;
class GUI;

class PalettePays : public cce::Palette
{
  
public :
  PalettePays();
  virtual ~PalettePays();
  void init(GUI const *gui, const string& conteneur, string nom, Carte* c);
  bool setSpawn(const CEGUI::EventArgs &e);
private :
  Carte* carte;
};

}

#endif // PALETTEPAYS_HPP
