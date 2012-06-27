#ifndef PALETTEPAYS_HPP
#define PALETTEPAYS_HPP

#include "cce/Palette.hpp"
#include <string>
#include <CEGUI/elements/CEGUIPushButton.h>

using std::string;

namespace edt{

class Controleur;
class Modele;
class GUI;

class PalettePays : public cce::Palette
{
  
public :
  PalettePays();
  virtual ~PalettePays();
  void init(GUI const *gui, string nom, Controleur* c, Modele* m);
  bool setSpawn(const CEGUI::EventArgs &e);
  bool onChangeSelection(const CEGUI::EventArgs &e);
private :
  Controleur* control;
  Modele* modele;
  CEGUI::Listbox* liste_pays;
  CEGUI::Editbox* box_nom;
};

}

#endif // PALETTEPAYS_HPP
