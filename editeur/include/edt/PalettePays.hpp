#ifndef PALETTEPAYS_HPP
#define PALETTEPAYS_HPP

#include "cce/Palette.hpp"
#include <string>

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
  bool onSelectionChange(const CEGUI::EventArgs &e);
  bool onNameChange(const CEGUI::EventArgs &e);
  bool onIncomeChange(const CEGUI::EventArgs &e);
  bool onNewPays(const CEGUI::EventArgs &e);
  bool onDeletePays(const CEGUI::EventArgs &e);
private :
  Controleur* control;
  Modele* modele;
  CEGUI::Listbox *liste_pays;
  CEGUI::Editbox *box_nom, *box_income;
  CEGUI::ListboxTextItem* current_pays_item;
};

}

#endif // PALETTEPAYS_HPP
