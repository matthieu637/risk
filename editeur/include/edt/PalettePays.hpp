#ifndef PALETTEPAYS_HPP
#define PALETTEPAYS_HPP

#include "cce/Palette.hpp"
#include <string>

using std::string;

namespace CEGUI{
class PushButton;
}

namespace edt{

class Controleur;
class Modele;
class GUI;

class PalettePays : public cce::Palette
{
  
public :
  PalettePays();
  virtual ~PalettePays();
  void init(GUI const *gui, const string& conteneur, string nom, Controleur* c);
  bool setSpawn(const CEGUI::EventArgs &e);
private :
  Controleur* control;
};

}

#endif // PALETTEPAYS_HPP
